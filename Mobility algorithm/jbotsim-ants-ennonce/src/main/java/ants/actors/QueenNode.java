package ants.actors;

import ants.environment.Cell;
import io.jbotsim.core.Node;

import java.util.Random;

public class QueenNode extends CellLocatedNode {

    private int foodStock;

    public QueenNode(){
        super();
        foodStock = 25;
        setIcon("/images/chest.png");
        setIconSize(getIconSize()*3);
    }

    @Override
    public void onClock() {
        if (shouldProduceOffspring())
            produceOffspring();
    }

    @Override
    public void onPostClock() {
        super.onPostClock();
    }

    private boolean shouldProduceOffspring() {
        return new Random().nextDouble() < 0.01;
    }

    public void produceOffspring(){
        if(foodStock <= 0) {
            this.die();
            return;
        }

        foodStock--;

        AntNode babyAnt = new AntNode(this);
        babyAnt.setCurrentCell(getCurrentCell());
        getTopology().addNode(babyAnt);
    }

    public void incrementFoodStock() {
        this.foodStock++;
    }

    @Override
    public String toString(){
        return "Stock nourriture " + this.foodStock;
    }
}
