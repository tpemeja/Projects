package ants.environment;

import ants.actors.CellLocatedNode;

import java.util.Random;

public class PheroNode extends CellLocatedNode {

    private double quantity;
    private int MAX_QUANTITY = 1;
    private int type;

    public PheroNode(int t){
        super();
        if(t==1){
            setIcon("/images/sign.png");
        }else{
            setIcon("/images/torche.png");
        }
        setIconSize(getIconSize());
        this.type = t;
        this.quantity = 0;
        setWirelessStatus(false);
        incrementQuantity();
    }

    protected void isDead() {
        if (this.quantity <= 0.0)
            this.die();
    }

    public boolean isQueenPhero() {
        return (this.type == 1);
    }

    public boolean isTunnelPhero() {
        return (this.type == 0);
    }

    protected void decrementQuantity() {
        if (this.getTime() % 500 == 0) {
            this.quantity = this.quantity - 0.1;
        }
    }

    @Override
    public void onClock() {
        this.decrementQuantity();
        this.isDead();
    }

    public void incrementQuantity() {
        if (this.quantity < this.MAX_QUANTITY) {
            this.quantity = quantity + 0.1;
        }
    }

    public double getQuantity(){
        return quantity;
    }

    @Override
    public void onPostClock() {
        super.onPostClock();
    }

    @Override
    public String toString(){
        return "Quantité restante" + this.quantity;
    }

}
