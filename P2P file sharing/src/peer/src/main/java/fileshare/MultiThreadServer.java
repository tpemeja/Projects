package fileshare;

/*
 * Server permettant de se connecter à d'autre pair afin de gérer la réception
 * de requêtes de la part des autres pairs
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;
import java.util.ArrayList;
import java.util.Base64;
import java.util.Map;
import java.util.logging.Logger;
import java.util.List;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.FileNotFoundException;

public class MultiThreadServer implements Runnable {

    protected int serverPort;
    protected ServerSocket serverSocket = null;
    protected boolean isStopped = false;
    protected Thread runningThread= null;

    private Parser parser;

    // mes buffermaps
    private Map<String, BufferMap> buffermaps;

    private final static Logger LOGGER = Logger.getLogger(MultiThreadServer.class.getName());


    public MultiThreadServer(int port){
        this.serverPort = port;
        this.buffermaps = new HashMap<String, BufferMap>();

        this.parser = new Parser();
        openServerSocket();
    }

    public void run(){
        synchronized(this){
            this.runningThread = Thread.currentThread();
        }
        while(!isStopped()){
            Socket clientSocket = null;
            try {
                clientSocket = this.serverSocket.accept();
                runCommand(clientSocket);
            } catch (IOException e) {
                if(isStopped()) {
                    LOGGER.warning("Server Stopped.") ;
                    return;
                }
                throw new RuntimeException("Error accepting client connection", e);
            }
        }
        LOGGER.warning("Server Stopped.");
    }

    // traitement d'une commande provenant d'un autre pair
    public void runCommand(Socket clientSocket) throws IOException {

        PrintWriter socketWriter = new PrintWriter(clientSocket.getOutputStream(), true);
        BufferedReader socketReader = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));

        String cmd = socketReader.readLine();
        ParsingResult r = parser.parse(cmd);
        // traitement de la requête
        String response = getResponse(r);
        // envoie de la réponse au pair
        socketWriter.println(response);

        clientSocket.close();
    }

    public void addBufferMap(String key, BufferMap bm) {
        buffermaps.put(key, bm);
    }

    public BufferMap getBufferMap(String key) {
        return buffermaps.get(key);
    }

    public List<String> getCurrentBufferMapKeys() {
        List<String> l = new ArrayList<String>();
        for(Map.Entry<String, BufferMap> m : buffermaps.entrySet()){
            if (((BufferMap)(m.getValue())).complete == false){
                l.add((String)(m.getKey()));
            }
        }
        return l;
    }

    // en fonction du parsing result de la commande fournie, la traite
    // et retourne une réponse pour le pair ayant demandé
    private String getResponse(ParsingResult r) {
        if(r.type() == CommandType.INTERESTED) {
            String key = r.getInterested();

            BufferMap bm = buffermaps.get(key);

            String response = null;
            if(bm != null) {
                response = "have " + key + " " + bm.toString();
            } else {
                response = "nok";
            }

            return response;
        }
        else if (r.type() == CommandType.GETPIECES){
            // récupérer la clé du fichier demandé
            String key = r.getKey();
            // récupérer le fichier en question
            BufferMap bm = buffermaps.get(key);
            if (bm == null){
                // erreur ! le fichier n'est pas en mémoire
                return "non j'ai pas ça";
            }
            // sinon on peut continuer
            // on récupère la liste des index
            List<Integer> index = r.getIndexGetPieces();

            if (bm.complete){
                // le fichier est complet et se trouve sur le disque
                InputStream file =  null;
                try {
                    file = new FileInputStream("./files/"+bm.filename);
                } catch(FileNotFoundException e) {
                    LOGGER.warning("Could not find required MD5 file. ERROR: " + e.getMessage());
                }
                byte[] buffer;

                // on parcours les morceaux de fichiers
                int numRead = 0;
                String response = "data " + key + " [";

                for(int p = 0; p < ((int)bm.fileSize / bm.pieceSize) + 1; p++){
                    try {
                        int toReadNext = (int) Math.min((int) bm.pieceSize, (int) bm.fileSize - p * (bm.pieceSize));
                        buffer = new byte[toReadNext];
                        numRead = file.read(buffer);
                        if (numRead < 0){
                            // erreur !
                            break;
                        }
                        if (index.contains(p)){
                            // on désire cette partie du fichier
                            String piece = new String(Base64.getEncoder().encode(buffer));
                            response += (Integer.toString(p) + ":" + piece + " ");
                        }
                    } catch(IOException e) {
                        LOGGER.warning("error in file pieces. ERROR: " + e.getMessage());
                        break;
                    }
                }
                return response + "]";
            }
            else{
                // on a certains morceaux du fichier dans la ram
                String response = "data " + key + " [";
                for(int p : index){
                    byte[] buffer = bm.getPiece(p);
                    if (buffer != null){
                        String piece = new String(Base64.getEncoder().encode(buffer));
                        response += (Integer.toString(p) + ":" + piece + " ");
                    }
                    else{
                        // erreur !
                        return "nok";
                    }

                }
                return response + "]";
            }

        }
        else if (r.type() == CommandType.HAVE){
            String response = null;
            response = "have "+ r.getKey() + " " + buffermaps.get(r.getKey()).toString();
            return response;
        }

        return "SHOULD NOT GET HERE";
    }

    public int getLocalPort() {
        return serverSocket.getLocalPort();
    }

    private synchronized boolean isStopped() {
        return this.isStopped;
    }

    public synchronized void stop(){
        this.isStopped = true;
        try {
            this.serverSocket.close();
        } catch (IOException e) {
            throw new RuntimeException("Error closing server", e);
        }
    }

    private void openServerSocket() {
        try {
            LOGGER.info("Opening server socket");
            this.serverSocket = new ServerSocket(this.serverPort);
        } catch (IOException e) {
            throw new RuntimeException("Cannot open port 8080", e);
        }
    }
}
