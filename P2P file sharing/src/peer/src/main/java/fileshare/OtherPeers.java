package fileshare;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class OtherPeers{
    private List<String> IP_port;
    private List<Map<String, BufferMap>> hs;


    public OtherPeers(){
        this.IP_port = new ArrayList<String>();
        this.hs = new ArrayList<Map<String, BufferMap>>();
    }

    // ne créer pas forcément un pair
    public int newPeer(String IP_port){
        for(int i = 0; i < this.IP_port.size(); i++){
            if (this.IP_port.get(i).equals(IP_port)){
                // comme ça on ne crée pas de doublons
                return i;
            }
        }
        this.IP_port.add(IP_port);
        this.hs.add(new HashMap<String, BufferMap>());
        return this.hs.size() -1; // retourne l'indice du pair créé
    }

    public String getIP_port(int index){
        return this.IP_port.get(index);
    }

    public void addBufferMap(int index, BufferMap bm){
        this.hs.get(index).put(bm.key, bm);
    }

    // mets à jour un buffermap à partir d'une string
    public void addBufferMap(int index, String key, String s_bm){
        BufferMap bm = this.hs.get(index).get(key);
        bm.resetBuffer(s_bm);
    }

    public List<String> getIPPortFromKey(String key){
        List<String> res = new ArrayList<String>();
        for(int i = 0; i < this.hs.size(); i++){
            if (this.hs.get(i).get(key) != null){
                res.add(this.IP_port.get(i));
            }
        }
        if (res.size() != 0){
            return res;
        }
        return null;
    }
}
