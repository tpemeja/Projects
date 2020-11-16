package ants.environment;

import ants.actors.CellLocatedNode;
import io.jbotsim.core.Node;

import java.util.Random;

public class FoodNode extends CellLocatedNode {

    public static final int MAX_QUANTITY = 20;
    public static final int MIN_QUANTITY = 1;
    private int quantity;

    public FoodNode(){
        super();
        Random r = new Random();
        setIcon("/images/diamant.png");

        setWirelessStatus(false);

        setDirection(new Random().nextDouble()*2*Math.PI);
        quantity = new Random().nextInt(MAX_QUANTITY) + MIN_QUANTITY;

        setIconSize(this.quantity);
    }

    protected void isDead() {
        if (this.quantity <= 0)
            this.die();
    }

    protected void decrementQuantity() {
        if (this.getTime() % 1000 == 0) {
            this.quantity--;
            if (this.quantity != 0)
                 this.setIconSize(this.quantity);
        }
    }

    public void incrementQuantity() {
        this.quantity++;
    }
    @Override
    public void onClock() {
        this.decrementQuantity();
        this.isDead();
    }

    @Override
    public void onPostClock() {
        super.onPostClock();
    }

    public void setQuantity(int quantity) {
        this.quantity = quantity;
        if (quantity <= 0) {
            this.die();
        }else{
            this.setIconSize(this.quantity);
        }
    }

    public int getQuantity(){
        return quantity;
    }

    @Override
    public String toString(){
        return "Quantité restante" + this.quantity;
    }

}
