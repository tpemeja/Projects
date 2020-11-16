package ants.environment;

import io.jbotsim.core.Point;

import java.util.HashMap;
import java.util.Map;
import java.util.Random;

public class Cell extends Point {

    public static final int MAX_COST_VALUE = 501;
    public static final int MIN_COST_VALUE = 1;
    private int cost;
    private int nbRow = 25;

    Map<Integer, Cell> neighBor = new HashMap<>();


    public Cell(Point location){
        super(location);
        cost = (int)(101 + (location.getZ()/nbRow)*(MAX_COST_VALUE-101));
        //cost = 30;
    }

    public Cell getNeighBor(int index) {
        return neighBor.get(index);
    }
    public void setNeighBor(int index, Cell value) {
        neighBor.put(index, value);
    }

    public static final int RIGHT = 0;
    public static final int LEFT = 1;
    public static final int TOP = 2;
    public static final int BOTTOM = 3;
    public static final int TOP_RIGHT = 4;
    public static final int BOTTOM_RIGHT = 5;
    public static final int BOTTOM_LEFT = 6;
    public static final int TOP_LEFT = 7;

    public Cell getRightNeighbor() {
        return getNeighBor(RIGHT);
    }
    public void setRightNeighbor(Cell neighbor) {
        setNeighBor(RIGHT, neighbor);
    }
    public Cell getLeftNeighbor() {
        return getNeighBor(LEFT);
    }
    public void setLefNeighbor(Cell neighbor) {
        setNeighBor(LEFT, neighbor);
    }
    public Cell getTopNeighbor() {
        return getNeighBor(TOP);
    }
    public void setTopNeighbor(Cell neighbor) {
        setNeighBor(TOP, neighbor);
    }
    public Cell getBottomNeighbor() {
        return getNeighBor(BOTTOM);
    }
    public void setBottomNeighbor(Cell neighbor) {
        setNeighBor(BOTTOM, neighbor);
    }

    public Cell getTopRightNeighbor() {
        return getNeighBor(TOP_RIGHT);
    }
    public void setTopRightNeighbor(Cell neighbor) {
        setNeighBor(TOP_RIGHT, neighbor);
    }
    public Cell getTopLeftNeighbor() {
        return getNeighBor(TOP_LEFT);
    }
    public void setTopLefNeighbor(Cell neighbor) {
        setNeighBor(TOP_LEFT, neighbor);
    }
    public Cell getBottomRightNeighbor() {
        return getNeighBor(BOTTOM_RIGHT);
    }
    public void setBottomRightNeighbor(Cell neighbor) {
        setNeighBor(BOTTOM_RIGHT, neighbor);
    }
    public Cell getBottomLeftNeighbor() {
        return getNeighBor(BOTTOM_LEFT);
    }
    public void setBottomLeftNeighbor(Cell neighbor) {
        setNeighBor(BOTTOM_LEFT, neighbor);
    }

    public int getCost() {
        return cost;
    }

    public void setCost(int cost) {
        this.cost = cost;
    }
    public void decrementCost() {
        cost--;
        if(cost < MIN_COST_VALUE)
            cost = MIN_COST_VALUE;
    }
    public int getMinCostValue() {
        return this.MIN_COST_VALUE;
    }

    @Override
    public String toString(){
        return "Cost restant" + this.cost;
    }
}
