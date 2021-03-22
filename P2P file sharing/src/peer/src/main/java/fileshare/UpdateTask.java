package fileshare;

import java.util.TimerTask;

public class UpdateTask extends TimerTask {
    Peer p;

    public UpdateTask(Peer p){
        // référence vers le pair
        this.p = p;
    }

  @Override
  public void run() {
    p.sendUpdateCommand();
  }
}
