package ants.environment;

import io.jbotsim.core.Topology;
import io.jbotsim.core.event.ClockListener;

import java.util.Random;

public class FoodSpawner implements ClockListener{

    private final Random random;
    private Topology tp;
    private Environment environment;

    public FoodSpawner(Topology topology, Environment environment) {
        tp = topology;
        this.environment = environment;
        tp.addClockListener(this);
        random = new Random();
    }

    @Override
    public void onClock() {

        if (shouldSpawn())
            spawnRandomFood();

    }

    int bottomFavoritism(int nbRow) {
        int length = (nbRow*(nbRow+1))/2;
        int[] prob = new int[length];
        int mult = 0;
        int tmp = nbRow;
        int index = 0;

        while(tmp > 0) {
            mult++;
            for(int i = 0; i < mult; i++) {
                prob[index] = mult-1;
                index++;
            }
            tmp--;
        }
        Random r = new Random();
        return prob[r.nextInt(length)];
    }

    public void spawnRandomFood() {
        FoodNode n = new FoodNode();
        int nbcol = environment.getNbColumn();
        int row = bottomFavoritism(environment.getNbRow());


        Random random = new Random();
        Cell location = environment.getElement(random.nextInt(nbcol-2)+1,row);
        n.setLocation(location);
        n.setCurrentCell(location);
        tp.addNode(n);
    }

    private boolean shouldSpawn() {
        return random.nextDouble() < 0.01;
    }
}
