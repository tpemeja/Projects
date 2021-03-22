package fileshare;

/*
 * un objet ParsingResult est crée par le parser après avoir lu une commande.
 * ParsingResult contient le type de la commande ainsi qu'un ensemble de couple
 * (key, value) permettant de retrouver les arguments d'une commande
 */


import java.util.Arrays;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.ArrayList;

class ParsingResult {

    private Map<String, List<String>> map;
    private CommandType type;

    // à la création on fixe le type
    ParsingResult(CommandType type) {
        map = new HashMap<String,List<String>>();
        this.type = type;
    }

    public void put(String key, String[] values) {
        map.put(key, Arrays.asList(values));
    }

    public void put(String key, String value) {
        List<String> values = new LinkedList<String>();
        values.add(value);
        map.put(key, values);
    }

    public CommandType type() {
        return type;
    }

    public int getPort() {
        if(type != CommandType.ANNOUNCE) {
            return -1; //TODO: better error handling ?
        }

        if(map.get("listen") == null) {
            return 0;
        }

        return Integer.parseInt(map.get("listen").get(0));
    }

    public void setPort(int port) {

        List<String> new_port = new LinkedList<String>();
        String strPort = Integer.toString(port);
        new_port.add(strPort);

        if(map.get("listen") == null) {
            map.put("listen", new_port);
        } else {
            map.get("listen").set(0, strPort);
        }
    }

    public List<Map<String, String>> getSeedFiles() {
        // if we're really picky about performance and time complexity, possible
        // we shouldn't calculate this everytime and we couldd possible replace
        // the list for another hashmap, but i don't think it's really needed

        if(type != CommandType.ANNOUNCE) {
            return null; //TODO: better error handling ?
        }

        List<String> filesAsList = map.get("seed");
        List<Map<String, String>> files = new LinkedList<Map<String,String>>();

        if(filesAsList == null) {
            return null;
        }

        for(int i = 0; i < filesAsList.size(); i += 4) {
            Map<String, String> fileConfig = new HashMap<String,String>();
            fileConfig.put("name", filesAsList.get(i));
            fileConfig.put("size", filesAsList.get(i+1));
            fileConfig.put("pieceSize", filesAsList.get(i+2));
            fileConfig.put("key", filesAsList.get(i+3));

            files.add(fileConfig);
        }

        return files;
    }

    public List<String> getLeechKeys() {

        if(type != CommandType.ANNOUNCE) {
            return null; //TODO: better error handling ?
        }

        return map.get("leech");
    }

    public List<String> getLookCriterions(){
        if (type == CommandType.LOOK){
            return map.get("criterions");
        }
        return null;
    }

    public List<String> getfileKeys(){
        if (type == CommandType.GETFILE){
            return map.get("keys");
        }
        return null;
    }

    public String getKey(){
        if (type == CommandType.GETPIECES || type == CommandType.HAVE){
            return map.get("key").get(0);
        }
        return null;
    }

    public String getBufferMap(){
        if (type == CommandType.HAVE){
            return map.get("buffermap").get(0);
        }
        return null;
    }

    public String getInterested() {
        if(type == CommandType.INTERESTED) {
            return map.get("interested").get(0);
        }
        return null;
    }

    public List<Integer> getIndexGetPieces(){
        if (type == CommandType.GETPIECES){
            List<Integer> l = new ArrayList<Integer>();
            for(String s : map.get("index").get(0).split(" ")){
                l.add(Integer.parseInt(s));
            }
            return l;
        }
        // sinon error
        return null;
    }

    @Override
    public String toString() {

        if(type == CommandType.ANNOUNCE) {

            String seedList;
            String leechList;

            if (map.get("seed") != null) {
                seedList = map.get("seed").toString().replace(",", "");
            } else {
                seedList = null;
            }

            if (map.get("leech") != null) {
                leechList = map.get("leech").toString().replace(",", "");
            } else {
                leechList = null;
            }

            if(leechList != null && seedList != null) {
                return "announce listen " + getPort() + " seed " + seedList + " leech " + leechList;
            } else if(leechList == null) {
                return "announce listen " + getPort() + " seed " + seedList + " leech []";
            } else if(seedList == null) {
                return "announce listen " + getPort() + " leech " + leechList + " seed []";
            }

        } else if(type == CommandType.LOOK) {
            return "look " + map.get("criterions").toString().replace("," , "");
        } else if (type == CommandType.GETFILE) {
            return "getfile " + map.get("keys").get(0);
        }

        return "";
    }
}
