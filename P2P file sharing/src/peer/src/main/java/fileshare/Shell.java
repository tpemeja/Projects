package fileshare;

/*
 * la class Shell permet de parser les commandes tapées par l'utilisateur
 * et de les faire traiter par la class Peer qui va alors interagir avec le
 * tracker
 */

import java.util.Timer;

public class Shell {

    private Parser parser;
    private Peer peer;

    public Shell(Parser parser, Peer peer) {
        this.parser = parser;
        this.peer = peer;
    }

    public void start() {
        System.out.println("<<< Welcome to FileShare >>>");

        Timer timer = new Timer();
        timer.schedule(new UpdateTask(this.peer), 500, Config.getInstance().getUpdatePeriod());

        if(Config.getInstance().shouldAutoAnnounce()) {
            String command = peer.getAutoAnnounceCommand();
            System.out.println("< " + command);
            ParsingResult r = parser.parse(command);
            String response = peer.run(r);
            System.out.println("> " + response);
        }

        while(true) {
            System.out.print("< ");
            String newCommand = System.console().readLine();
            // transformer la commande en objet contenant des pairs
            // le résultat sera alors interprété par le peer
            ParsingResult r = parser.parse(newCommand);

            if(newCommand.equals("exit")) {
                return;
            } else if (r != null) {
                String response = peer.run(r);
                System.out.println("> " + response);
            } else {
                System.out.println("< Command \"" + newCommand + "\" not valid");
            }
        }
    }
}
