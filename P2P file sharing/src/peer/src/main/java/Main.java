import java.io.File;
import java.io.IOException;
import java.util.logging.Logger;

import fileshare.Config;
import fileshare.MD5;
import fileshare.Parser;
import fileshare.Peer;
import fileshare.Shell;

public class Main {

    private final static Logger LOGGER = Logger.getLogger(Main.class.getName());
    public static void main(String[] args){

        if(args.length != 0) {
            LOGGER.info("Will forcibly run peer server on port " + args[0]);
            int peerPort = Integer.parseInt(args[0]);
            // récupérer les config du fichier config.ini
            Config.getInstance().setPeerPort(peerPort);
        }

        // affiche les fichiers disponibles
        displayFileInfos();

        Peer peer;

        try {
            peer = new Peer(); // échoue en cas de tracker indisponible
        } catch (IOException e) {
            LOGGER.severe("Failed starting application. ERROR: " + e.getMessage());
            String ip = Config.getInstance().getTrackerIp();
            int port = Config.getInstance().getTrackerPort();
            LOGGER.severe("Make sure the C Tracker application is running on " + ip + ":" + port);
            return;
        }

        Parser parser = new Parser();
        Shell shell = new Shell(parser, peer);
        shell.start();
    }

    // parcours le répertoire ./files à la recherche des fichiers diponibles
    // pour le transfert à d'autres pairs
    private static void displayFileInfos() {
        File folder = new File("files/");
        File[] listOfFiles = folder.listFiles();

        MD5 md5 = new MD5();

        System.out.println("<< LISTING ALL PEER KNOWN FILES >>");
        for (int i = 0; i < listOfFiles.length; i++) {
            if (listOfFiles[i].isFile()) {

                String filename = listOfFiles[i].getName();
                System.out.println("Name: " + filename + " Size: " + listOfFiles[i].length() + " Hash: " + md5.getMD5(filename));
            }
        }
        System.out.println("<< END LISTING ALL PEER KNOWN FILES >>\n");

    }
}
