package fileshare;

import java.io.FileOutputStream;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Logger;

class BufferMap {

    public String filename;
    public String key;
    public int pieceSize;
    public long fileSize;
    private int bufferSize;
    // les morceaux de fichiers ne sont utilisés que pour les buffermap des
    // fichiers que l'on possède nous-même
    private List<byte[]> pieces;
    public boolean complete = false; // faux => on a (peut-être) des morceaux
                                    // mais pas tout
                                    // vrai => il est sur le disque

    public boolean empty = false;
    private List<Integer> buffer;

    private final static Logger LOGGER = Logger.getLogger(MultiThreadServer.class.getName());
    BufferMap(String filename, long fileSize, int pieceSize, String key, int fill_value) {
        this.filename = filename;
        this.fileSize = fileSize;
        this.pieceSize = pieceSize;
        this.key = key;

        this.bufferSize = ((int)this.fileSize / this.pieceSize) + 1;
        this.buffer = new ArrayList<Integer>(bufferSize);

        this.pieces = new ArrayList<byte[]>(bufferSize);

        for(int i = 0; i < bufferSize; i++) {
            this.buffer.add(fill_value);
            this.pieces.add(null);
        }
        if (fill_value == 1){
            this.complete = true;
        }

        if(fill_value == 0) {
            this.empty = true;
        }
    }

    BufferMap(String filename, long fileSize, int pieceSize, String key, String buffermap) {
        this.filename = filename;
        this.fileSize = fileSize;
        this.pieceSize = pieceSize;
        this.key = key;

        this.bufferSize = ((int)this.fileSize / this.pieceSize) + 1;
        this.buffer = new ArrayList<Integer>(bufferSize);

        this.pieces = new ArrayList<byte[]>(bufferSize);

        for(int i = 0; i < bufferSize; i++) {
            this.buffer.add(Integer.parseInt(""+buffermap.charAt(i)));
            this.pieces.add(null);
        }
    }

    public void resetBuffer(String newBufferMap){
        this.buffer = new ArrayList<Integer>(bufferSize);
        this.pieces = new ArrayList<byte[]>(bufferSize);
        for(int i = 0; i < bufferSize; i++) {
            this.buffer.add(Integer.parseInt(""+newBufferMap.charAt(i)));
            this.pieces.add(null);
        }
    }

    public void addPiece(int index, byte[] piece){
        this.empty = false;
        this.pieces.set(index, piece);
        this.buffer.set(index, 1);
        for(byte[] b : this.pieces){
            if (b == null){
                return ;
            }
        }
        this.complete = true;
        this.saveBufferMapAsfile();
    }

    public void saveBufferMapAsfile() {
        File file = new File("files/" + filename);
        if (file.exists() && file.isFile()) {
            file.delete();
        }

        
        LOGGER.info("Will save file " + filename + " to disk !");
        try {
            file.createNewFile();
        } catch (IOException  e) {
            LOGGER.warning("Failed to create file to save buffer map");
        }

        FileOutputStream fos = null;
        try {
            fos = new FileOutputStream("files/" + filename);
        } catch (FileNotFoundException e) {
            LOGGER.warning("Failed to create file to save buffer map");
        }

        for(byte [] piece: pieces) {
            try {
                fos.write(piece);
            } catch (IOException e) {
                LOGGER.warning("Failed to write buffermap to file");
            }
        }

        try {
            fos.close();
        } catch (IOException e) {
            LOGGER.warning("Failed to save content to/close file");
        }
        LOGGER.info("Finished saving file " + filename + " to disk !");


    }

    public byte[] getPiece(int index){
        if (index > this.bufferSize){
            // erreur, out of range
            return null;
        }
        if (this.buffer.get(index) == 1){
            return this.pieces.get(index);
        }
        // erreur
        return null;
    }

    public boolean isEmpty() {
        return empty;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder(buffer.size());

        for(Integer value : buffer) {
            sb.append(Integer.toString(value));
        }

        return sb.toString();
    }

}
