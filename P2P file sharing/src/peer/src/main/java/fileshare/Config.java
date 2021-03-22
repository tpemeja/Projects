package fileshare;

/*
 * classe permettant de récupérer les données du fichier de configuration
 * l'objet doit être manipulé via la méthode getInstance
 * ainsi, le fichier n'est ouvert qu'une seule fois
 */

import java.io.ByteArrayInputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.Charset;
import java.util.Properties;
import java.util.logging.Logger;

public class Config {

    private final static Logger LOGGER = Logger.getLogger(Config.class.getName());
    private final static String defaultConfig = "tracker-address=127.0.0.1\ntracker-port=8090\npeer-port=0";

    private static Config instance = null;

    private Properties prop;
    private int peerPort = 0;

    public static Config getInstance() {
        if (instance == null) {
            instance = new Config();
        }
        return instance;
    }

    public String getTrackerIp() {
        return prop.getProperty("tracker-address");
    }

    public int getTrackerPort() {
        return Integer.parseInt(prop.getProperty("tracker-port"));
    }

    public boolean shouldAutoAnnounce() {
        return Boolean.parseBoolean(prop.getProperty("auto-announce"));
    }

    public int defaultPieceSize() {
        return Integer.parseInt(prop.getProperty("default-piece-size"));
    }

    public int getPeerPort() {
        if(peerPort != 0) {
            return peerPort;
        }
        return Integer.parseInt(prop.getProperty("peer-port"));
    }

    public void setPeerPort(int peerPort) {
        this.peerPort = peerPort;
    }

    public int getUpdatePeriod(){
        return Integer.parseInt(prop.getProperty("update-period"));
    }

    public boolean getDisplayUpdate() {
        return Boolean.parseBoolean(prop.getProperty("display-update"));
    }

    // constructeur privé, l'objet ne sera instancié qu'une unique fois via la
    // méthode getInstance afin de faire en sorte que le fichier ne soit lu
    // qu'une fois
    private Config() {

        prop = new Properties();
        InputStream input;
        try {
            input = new FileInputStream("config.ini");
            LOGGER.info("Config file found in " + System.getProperty("user.dir") + ". Using this file !");

        } catch(FileNotFoundException e) {
            LOGGER.warning("Could not find config file. Starting with default config. MESSAGE: " + e.getMessage());
            input = new ByteArrayInputStream(defaultConfig.getBytes(Charset.forName("UTF-8")));
        }

        try {
            prop.load(input);
        } catch(IOException e) {
                LOGGER.severe("Failed reading config file. ERROR: " + e.getMessage());
                System.exit(1);
            }
        }
}
