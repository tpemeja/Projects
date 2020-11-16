package ants.actors;

import ants.environment.Cell;
import io.jbotsim.core.Node;

public class    CellLocatedNode extends WaypointNode {

    protected Cell currentCell = null;


    public Cell getCurrentCell() {
        return currentCell;
    }

    public void setCurrentCell(Cell currentCell) {
        this.currentCell = currentCell;
    }

}
