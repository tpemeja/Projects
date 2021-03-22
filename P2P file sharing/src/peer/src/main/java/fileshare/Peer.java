package fileshare;

/*
 * La classe Peer retransmet les commandes utilisateur reçues via le shell
 * puis elle utilise un DownloadManager ...
 *
 */


import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.logging.Logger;

public class Peer {

    private static final Logger LOGGER = Logger.getLogger(Peer.class.getName());

    private static final int TRACKER_PORT = Config.getInstance().getTrackerPort();
    private static final String TRACKER_IP = Config.getInstance().getTrackerIp();

    private Socket trackerSocket;
    private PrintWriter socketWriter;   // pour répondre au tracker
    private BufferedReader socketReader;// pour recevoir les messages du tracker
    private MD5 md5;
    private DownloadManager dm;

    public Peer() throws IOException {
        dm = new DownloadManager();
        trackerSocket = new Socket(TRACKER_IP, TRACKER_PORT);
        socketWriter = new PrintWriter(trackerSocket.getOutputStream(), true);
        socketReader = new BufferedReader(new InputStreamReader(trackerSocket.getInputStream()));
        md5 = new MD5();
    }

    // interprète le parsing result pour transmettre la requête au tracker
    public String run(ParsingResult r) {

        if(r.type() == CommandType.ANNOUNCE) {
            return handleAnnounce(r);
        } else if(r.type() == CommandType.LOOK) {
            return handleLook(r);
        } else if(r.type() == CommandType.GETFILE) {
            return handleGetFile(r);
        } else if(r.type() == CommandType.INTERESTED) {
            return handleInterested(r);
        } else if(r.type() == CommandType.GETPIECES){
            return handleGetPieces(r);
        }

        return "ok";
    }

    public String getAutoAnnounceCommand() {

        File folder = new File("files/");
        File[] listOfFiles = folder.listFiles();

        StringBuilder command = new StringBuilder();

        int peerPort = dm.getRunningPort();

        command.append("announce listen " + peerPort + " seed [");

        for (int i = 0; i < listOfFiles.length; i++) {
            if (listOfFiles[i].isFile()) {

                String filename = listOfFiles[i].getName();
                command.append(filename + " ");
                command.append(listOfFiles[i].length() + " ");
                command.append(Config.getInstance().defaultPieceSize() + " ");
                command.append(md5.getMD5(filename) + " ");
            }
        }
        if (command.charAt(command.length()-1) != '['){
            command.deleteCharAt(command.length()-1); // enlever le dernier espace en trop
        }

        command.append("]");
        return command.toString();
    }

    // envoyer périodiquement les clés en seed et en leech
    public void sendUpdateCommand() {
        File folder = new File("files/");
        File[] listOfFiles = folder.listFiles();
        StringBuilder command = new StringBuilder();
        command.append("update seed [");

        for (int i = 0; i < listOfFiles.length; i++) {
            if (listOfFiles[i].isFile()) {
                String filename = listOfFiles[i].getName();
                command.append(md5.getMD5(filename) + " ");
            }
        }
        if (command.charAt(command.length()-1) != '['){
            command.deleteCharAt(command.length()-1); // enlever le dernier espace en trop
        }
        command.append("] leech [");

        // on parcours les clés des fichiers qu'on n'a pas entièrement
        for(String key : dm.getCurrentBufferMapKeys()){
            command.append(key + " ");
        }
        if (command.charAt(command.length()-1) != '['){
            command.deleteCharAt(command.length()-1); // enlever le dernier espace en trop
        }
        command.append("]");

        // envoie la commande d'update au tracker
        socketWriter.println(command);

        String response;
        try {
            // réponse du tracker
            response = socketReader.readLine();

        } catch (IOException e) {
            response = "something wrong happened during update" + "\nERROR: " + e.getMessage();
            LOGGER.warning("something wrong happened during update " + "ERROR: " + e.getMessage());
        }

        if(Config.getInstance().getDisplayUpdate()) {
            System.out.println("< " + command);
            System.out.println("> " + response);
        }
    }

    private String handleAnnounce(ParsingResult r) {

        int peerPort = dm.getRunningPort();
        r.setPort(peerPort);

        // convertit toutes les seeds en buffermaps puis les ajoutes dans la base
        // de données du server
        dm.startBufferMaps(r.getSeedFiles());

        // envoie la commande d'announce au tracker
        socketWriter.println(r);
        String response;
        try {
            // réponse du tracker
            response = socketReader.readLine();

        } catch (IOException e) {
            response = "not ok from tracker, tried on port = " + peerPort + "\nERROR: " + e.getMessage();
            LOGGER.warning("Failed to receive message from tracker on port = " + peerPort + "ERROR: " + e.getMessage());
        }
        return response;
    }

    private String handleLook(ParsingResult r) {

        // envoie de la commande look au tracker
        socketWriter.println(r);
        String response;

        try {
            // réponse du tracker
            response = socketReader.readLine();
        } catch(IOException e) {
            response = "Error from tracker connection" + "\nERROR: " + e.getMessage();
            LOGGER.severe("Failed to receive message from tracker" + "ERROR: " + e.getMessage());
        }
        if(!response.equals("nok")) {
            // si tout s'est bien passé, on stocke les infos dans le DownloadManager
            dm.handleLookAnswer(response);
        }

        return response;
    }

    private String handleGetFile(ParsingResult r) {
        // envoie de la commande getFile au tracker
        socketWriter.println(r);
        String response;

        try {
            // réponse du tracker
            response = socketReader.readLine();
        } catch(IOException e) {
            response = "Error from tracker connection" + "\nERROR: " + e.getMessage();
            LOGGER.severe("Failed to receive message from tracker" + "ERROR: " + e.getMessage());
        }

        if(!response.equals("nok")) {
            // si tout s'est bien passé, on stocke les infos dans le DownloadManager
            dm.handleGetFileAnswer(response);
        }

        return response;
    }

    private String handleInterested(ParsingResult r) {

        // la clé qui nous intéresse
        String key = r.getInterested();

        BufferMap bm = dm.getBufferMap(key);

        String response = null;
        if(bm != null && !bm.isEmpty()) {
            response = "have " + key + " " + bm.toString();
        } else {
            try {
                response = dm.getBufferMapFromPeers(key);
            } catch(IOException e) {
                LOGGER.warning("Error trying to get buffer map from peers");
                response = "error";
            }
        }

        return response;
    }

    private String handleGetPieces(ParsingResult r){
        // demander au DownloadManager de demander à un autre pair (qui possède
        // le fichier en question) de lui transférer
        String response = null;
        try{
            response = dm.getPieces(r.getKey(), r.getIndexGetPieces());
            // une fois les données reçues, il faut envoyer le nouveau buffermap aux autres
            if (!response.equals("error")){
                dm.sendHaveToAll(r.getKey());
            }    
        } catch(IOException e) {
            LOGGER.warning("Error trying to get pieces from peers");
            response = "error";
        }
        return response;
    }
}
