package fileshare;

/*
 * Le DownloadManager est en charge de traiter les réponses du tracker et
 * d'envoyer des requêtes aux autres pairs. Il possède un server pour réagir aux
 * demandes des autres pairs.
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Base64;
import java.util.List;
import java.util.Map;
import java.util.logging.Logger;

class DownloadManager {

    private final static Logger LOGGER = Logger.getLogger(DownloadManager.class.getName());

    // récupérer le port depuis le fichier config.ini
    private int port = Config.getInstance().getPeerPort();
    // server pour gestion des commandes
    private MultiThreadServer server;

    private Socket peerSocket;
    private PrintWriter socketWriter;
    private BufferedReader socketReader;

    // map entre une key et map entre IP:port et buffermap
    private OtherPeers peers;

    DownloadManager() throws IOException {
        server = new MultiThreadServer(port);

        // lancement d'une server, en attente de client
        new Thread(server).start();
        port = server.getLocalPort();

        LOGGER.info("Starting server at port: " + port);

        peers = new OtherPeers();
    }

    public int getRunningPort() {
        return port;
    }

    // récupère la réponse du tracker pour getFile
    public void handleGetFileAnswer(String result) {
        // result est la réponse du tracker

        result = result.replace("[", "");
        result = result.replace("]", "");

        String[] s = result.split(" ");

        String[] values = Arrays.copyOfRange(s, 2, s.length);

        // mettre un nouveau buffermap pour ce pair mais vide pour l'instant
        // le mien que j'ai créer avec look
        BufferMap mybm = server.getBufferMap(s[1]);
        if (mybm == null){
            //erreur il fallait faire un look !
            // TODO
            return;
        }

        List<String> pairs = new ArrayList<String>(Arrays.asList(values));
        for(String IP_port : pairs){
            // créer ou récupérer le pair pour IP:port
            int index = peers.newPeer(IP_port);
            // créer un buffermap vide
            BufferMap newbm = new BufferMap(mybm.filename, mybm.fileSize, mybm.pieceSize, mybm.key, 0);
            peers.addBufferMap(index, newbm);
        }
        // (key, ["IP:port", ...])
        //peers.put(s[1], pairs);
    }

    // récupère la réponse du tracker pour look
    public void handleLookAnswer(String result){
        // result = list [$Filename1 $Length1 $PieceSize1 $Key1 $Filename2 $Length2 $PieceSize2 $Key2 …]
        result = result.replace("[", "");
        result = result.replace("]", "");

        String[] s = result.split(" ");
        if (s[1].equals("nok")){
            return;
        }

        for(int i = 1; i < s.length; i+=4){
            String name = s[i];
            String fileSize = s[i+1];
            String pieceSize = s[i+2];
            String key = s[i+3];

            BufferMap bm = new BufferMap(name, Long.parseLong(fileSize),  Integer.parseInt(pieceSize), key,  0);

            server.addBufferMap(key, bm);
        }
    }

    // ajoute les informations concernant un fichier dans la 'base de données'
    // du server
    public void addBufferMap(String key, BufferMap bm) {
        server.addBufferMap(key, bm);
    }

    // récupère les informations concernant un fichier dans la 'base de données'
    // du server
    public BufferMap getBufferMap(String key) {
        return server.getBufferMap(key);
    }

    // récupère les clés des fichiers en cours de téléchargements
    public List<String> getCurrentBufferMapKeys() {
        return server.getCurrentBufferMapKeys();
    }

    // correspond à l'envoie de la commande interested aux autres pairs
    public String getBufferMapFromPeers(String key) throws IOException {
        // liste de pairs qui possède ce fichier d'après le tracker
        List<String> availablePeers = peers.getIPPortFromKey(key);

        StringBuilder sb = new StringBuilder();
        String response = "";

        if (availablePeers == null){
            LOGGER.warning("No available Peer");
            return "error";
        }

        for(String IP_port : availablePeers) {

            String[] s = IP_port.split(":");
            peerSocket = new Socket(s[0], Integer.parseInt(s[1]));
            socketWriter = new PrintWriter(peerSocket.getOutputStream(), true);
            socketReader = new BufferedReader(new InputStreamReader(peerSocket.getInputStream()));

            // envoie de la commande interested au pair
            socketWriter.println("interested " + key);
            // stockage de la réponse
            response = socketReader.readLine();
            sb.append(response);
            peerSocket.close();

            // stocker la réponse
            // > have key buffermap
            String[] rep = response.split(" ");
            if (rep[0].equals("have")){
                // récupérer l'index du pair
                int index = peers.newPeer(IP_port);
                // mettre à jour le buffermap
                peers.addBufferMap(index, rep[1], rep[2]);
            }

        }
        // retourne l'ensemble des réponses des pairs sous forme de string
        return sb.toString();

    }

    // convertit toutes les seeds en buffermaps puis les ajoutes dans la 'base
    // de données' du server
    public void startBufferMaps(List<Map<String, String>> seeds) {
        for(Map<String, String> seed: seeds) {

            String name = seed.get("name");
            String fileSize = seed.get("size");
            String pieceSize = seed.get("pieceSize");
            String key = seed.get("key");

            BufferMap bm = new BufferMap(name, Long.parseLong(fileSize),  Integer.parseInt(pieceSize), key,  1);

            server.addBufferMap(key, bm);
        }
    }

    // trouver un pair qui posséde le fichier et lui demander les morceaux
    public String getPieces(String key, List<Integer> index) throws IOException {
        List<String> IP_port = peers.getIPPortFromKey(key);
        if (IP_port == null){
            // on ne connait personne possédant ce fichier
            LOGGER.warning("No available Peer for this key");
            return "error";
        }
        String IP = IP_port.get(0).split(":")[0];
        int port = Integer.parseInt(IP_port.get(0).split(":")[1]);

        // établir une connexion avec le pair (IP, port)
        // et envoyer la requête getpieces key [ index ]
        peerSocket = new Socket(IP, port);
        socketWriter = new PrintWriter(peerSocket.getOutputStream(), true);
        socketReader = new BufferedReader(new InputStreamReader(peerSocket.getInputStream()));
        // envoie de la commande interested au pair
        socketWriter.println("getpieces "+key+" "+Arrays.toString(index.toArray()).replace(",", ""));
        // stockage de la réponse
        String response = socketReader.readLine();
        //String response = new String(Base64.getDecoder().decode(rawResponse));


        // traitement de la réponse
        BufferMap bm = server.getBufferMap(key);
        if (bm == null){
            // erreur, fichier inconnu
            // il fallait faire un look avant pour avoir le détails !
            return "error";
        }

        StringBuilder displayResponse = new StringBuilder();
        displayResponse.append("data " + key + " [");

        String parsingResponse = "";
        if(response.charAt(response.length() - 1) == ']' && response.charAt(response.length() - 2) == ' ') {
            parsingResponse = response.substring(0, response.length() - 2);
        }

        if (parsingResponse.startsWith("data")){
            // tout va bien
            int cur = parsingResponse.indexOf("[");

            parsingResponse = parsingResponse.substring(cur+1, parsingResponse.length());

            for(String pieceWithNumber: parsingResponse.split(" ")) {
                String[] pair = pieceWithNumber.split(":");
                
                int idx = Integer.parseInt(pair[0]);
                
                byte[] idxContent;
                try {
                    String piece = pair[1];
                    idxContent = Base64.getDecoder().decode(piece);

                    displayResponse.append(idx + ":" + new String(idxContent) + " ");

                } catch (ArrayIndexOutOfBoundsException e) {
                    idxContent = "".getBytes();
                }
                bm.addPiece(idx, idxContent);
            }
        }
        else{
            //erreur
            LOGGER.warning("getpieces error");
        }

        peerSocket.close();

        displayResponse.append("]");

        return displayResponse.toString();
    }

    public void sendHaveToAll(String key) throws IOException{
        for(String IP_port : peers.getIPPortFromKey(key)){
            String IP = IP_port.split(":")[0];
            int port = Integer.parseInt(IP_port.split(":")[1]);
            // établir une connexion avec le pair (IP, port)
            // et envoyer la requête getpieces key [ index ]
            peerSocket = new Socket(IP, port);
            socketWriter = new PrintWriter(peerSocket.getOutputStream(), true);
            socketReader = new BufferedReader(new InputStreamReader(peerSocket.getInputStream()));
            // envoie de la commande have au pair
            socketWriter.println("have "+key+" "+server.getBufferMap(key).toString());
            // stockage de la réponse
            String response = socketReader.readLine();

            // mise à jour des peers
            // stocker la réponse
            // > have key buffermap
            String[] s = response.split(" ");
            if (s.length != 3){
                // erreur !
                LOGGER.warning("send Have to all receive error");
                return;
            }
            if (s[0].equals("have")){
                // récupérer l'index du pair
                int index = peers.newPeer(IP_port);
                // mettre à jour le buffermap
                peers.addBufferMap(index, s[1], s[2]);
            }
        }
    }
}
