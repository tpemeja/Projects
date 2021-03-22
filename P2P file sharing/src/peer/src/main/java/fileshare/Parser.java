package fileshare;

/*
 * la classe Parser permet au pair de vérifier la validité des commandes entrées
 * par l'utilisateur
 * Le parsing retourne un objet de type ParsingResult qui contient le type de la
 * commande ainsi qu'un ensemble de couple (key, value) permettant de retrouver
 * les arguments d'une commande
 */


import java.util.Arrays;

public class Parser {
    public Parser(){}

    // requête du pair announce
    private ParsingResult parse_announce(String[] str){
        ParsingResult announce = new ParsingResult(CommandType.ANNOUNCE);

        for(int i = 1; i < str.length; i++) {
            if(str[i].equals("listen")) {
                announce.put("listen", str[i+1]);
                i++;
            }

            if(str[i].equals("seed")) {
                int start = i+1;
                while(i+1 < str.length && !str[i+1].equals("listen") && !str[i+1].equals("leech")) {
                    i++;
                }
                String[] slice = Arrays.copyOfRange(str, start, Math.min(i+1, str.length));
                announce.put("seed", slice);
            }

            if(str[i].equals("leech")) {
                int start = i+1;
                while(i+1 < str.length && !str[i+1].equals("listen") && !str[i+1].equals("seed")) {
                    i++;
                }
                String[] slice = Arrays.copyOfRange(str, start, Math.min(i+1, str.length));
                announce.put("leech", slice);
            }
        }

        return announce;
    }

    // requête du pair look
    private ParsingResult parse_look(String[] str){
        ParsingResult look = new ParsingResult(CommandType.LOOK);
        // on sauve les critères dans un tableau
        // chaque critère est une string de la forme : filename="nom.dat"
        look.put("criterions", Arrays.copyOfRange(str, 1, str.length));
        return look;
    }

    // requête du pair getfile
    private ParsingResult parse_getfile(String[] str){
        ParsingResult getfile = new ParsingResult(CommandType.GETFILE);
        // on sauve la liste des clés dans un tableau
        getfile.put("keys", Arrays.copyOfRange(str, 1, str.length));
        return getfile;
    }

    // requête du pair interested
    private ParsingResult parse_interested(String[] str) {
        ParsingResult interested = new ParsingResult(CommandType.INTERESTED);

        interested.put("interested", str[1]);
        return interested;
    }

    // réponse du tracker à la commande look
    private ParsingResult parse_getpieces(String[] str){
        ParsingResult r = new ParsingResult(CommandType.GETPIECES);
        // getpieces $Key [$Index1 $Index2 $Index3 …]
        r.put("key", str[1]);
        String list = "";
        for(int i = 2; i < str.length; i++){
            list += (str[i] + " ");
        }
        r.put("index", list);
        return r;
    }

    private ParsingResult parse_have(String[] str){
        ParsingResult r = new ParsingResult(CommandType.HAVE);
        // have $Key $buffermap
        r.put("key", str[1]);
        r.put("buffermap", str[2]);
        return r;
    }

    public ParsingResult parse(String str){

        str = str.replace("[", "");
        str = str.replace("]", "");

        String[] s = str.split(" ");

        if (s[0].equals("announce")){
            return parse_announce(s);
        } else if (s[0].equals("look")) {
            return parse_look(s);
        } else if (s[0].equals("getfile")) {
            return parse_getfile(s);
        } else if (s[0].equals("interested")) {
            return parse_interested(s);
        } else if (s[0].equals("getpieces")) {
            return parse_getpieces(s);
        } else if (s[0].equals("have")){
            return parse_have(s);
        }

        return null;
    }
}
