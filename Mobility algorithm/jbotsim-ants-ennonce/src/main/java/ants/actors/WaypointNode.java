package ants.actors;

import ants.environment.Cell;
import io.jbotsim.core.Node;
import io.jbotsim.core.Point;

import java.util.LinkedList;
import java.util.Queue;

/**
 * This type of Node can move over a sequence of destinations,
 * specified through the addDestination() method.
 */
public class WaypointNode extends Node {
    Queue<Cell> destinations = new LinkedList<Cell>();
    int speed = 1;

    @Override
    public void onClock() {
        if ( ! destinations.isEmpty() ){
            Cell dest = destinations.peek();
            if (distance(dest) > speed) {
                setDirection(dest);
                move(speed);
            }else{
                setLocation(dest);
                onArrival(destinations.poll());
            }
        }
    }

    @Override
    public void onStart() {}
    public void setSpeed(int speed) {
        this.speed = speed;
    }

    public void addDestination(Cell destination){
        destinations.add(destination);
    }

   /* public void addDestination(double x, double y){
        addDestination(new Point(x, y));
    }*/

    public void onArrival(Cell c){}
}