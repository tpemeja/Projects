package fileshare;

/*
 * Permet de produire une clé à partir d'un fichier en utilisant le hashage MD5
 */

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.logging.Logger;


public class MD5 {
    private static final Logger LOGGER = Logger.getLogger(MD5.class.getName());
    private String path = "files/";

    public MD5() {}

    public MD5(final String path) {
        this.path = path;
    }

    private byte[] createChecksum(String filename) {
        InputStream fis =  null;
        try {
            fis = new FileInputStream(path + filename);
        } catch(FileNotFoundException e) {
            LOGGER.warning("Could not find required MD5 file. ERROR: " + e.getMessage());
        }

        byte[] buffer = new byte[1024];
        MessageDigest complete = null;
        try {
            complete = MessageDigest.getInstance("MD5");
        }catch(NoSuchAlgorithmException e) {
            LOGGER.severe(e.getMessage());
        }

        int numRead = 0;

        do {
            try {
                numRead = fis.read(buffer);
            } catch(IOException e) {
                LOGGER.warning("Could not get file MD5. ERROR: " + e.getMessage());
            }
            if (numRead > 0) {
                complete.update(buffer, 0, numRead);
            }
        } while (numRead != -1);

        try {
            fis.close();
        } catch (IOException e) {
            LOGGER.warning("Could not close MD5 file input stream. ERROR: " + e.getMessage());
        }


        return complete.digest();
    }


    public String getMD5(final String fileName) {

        byte[] b = createChecksum(fileName);
        String result = "";

        for (int i=0; i < b.length; i++) {
            result += Integer.toString( ( b[i] & 0xff ) + 0x100, 16).substring( 1 );
        }

        while(result.length() < 32 ){
            result = "0"+result;
        }
        return result;
    }

    // retourne le filename du fichier possédant la clé key
    public String getFilename(String key) {
        File dir = new File(path);
        File[] directoryListing = dir.listFiles();

        for (File child : directoryListing) {
            if(checkMD5(child.getName(), key)) {
                return child.getName();
            }
        }

        return null;

    }

    // vérifie si un clé correspond bien à un fichier
    public Boolean checkMD5(final String fileName, final String md5Hash) {
        final String checksum = getMD5(fileName);
        return md5Hash.equals(checksum);
    }
}
