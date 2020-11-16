package ants.actors;

import ants.environment.Cell;
import ants.environment.FoodNode;
import ants.environment.PheroNode;
import io.jbotsim.core.Color;
import io.jbotsim.core.Node;
import io.jbotsim.core.Point;

import java.util.ArrayList;
import java.util.List;
import java.util.Queue;
import java.util.Random;

public class AntNode extends CellLocatedNode {

    int beanSensed = 0;
    FoodNode nodeSensed;
    QueenNode queen;
    int survivalTime;
    int opposedDirection;
    int currentDirection;
    int createPheroTunnel;
    int needTunnel = 1;
    Cell lastCellMemory;

    /* Initialisation d'une fourmi */
    public AntNode(QueenNode q){
        super();
        Random r = new Random();
        this.survivalTime = 1000 + r.nextInt(1000);
        this.queen = q;
        this.setSpeed(30); // 30 pour éviter un bug de déplacement impossible
        setIcon("/images/kevin-pioche.png");
        setIconSize((getIconSize()*5)/2);
    }


    /* Override ici pour permettre un visuel plus réaliste
    * Il est seulement question de donner la bonne image aux fourmis
    * lors d'un déplacement */
    @Override
    public void setDirection(Point p) {
        Cell c = (Cell) p;
        super.setDirection(p);
        if(this.getCurrentCell().getRightNeighbor()==null){
            if(this.getIcon().equals("/images/kevin-pioche-1.png")){
                return;
            }
            if(this.getIcon().equals("/images/kevin-pioche-3.png")){
                this.setIcon("/images/kevin-pioche-1.png");
                return;
            }
            if(this.getIcon().equals("/images/kevin-diamant-1.png")){
                return;
            }
            if(this.getIcon().equals("/images/kevin-diamant-3.png")){
                this.setIcon("/images/kevin-diamant-1.png");
                return;
            }
        }
        if(this.getCurrentCell().getRightNeighbor()!=null&&this.getCurrentCell().getRightNeighbor().equals(c)){
            if(this.getIcon().equals("/images/kevin-pioche-3.png")){
                return;
            }else{
                if(this.getIcon().equals("/images/kevin-pioche.png")
                ||this.getIcon().equals("/images/kevin-pioche-1.png")
                 ||this.getIcon().equals("/images/kevin-pioche-2.png")){
                this.setIcon("/images/kevin-pioche-3.png");
                return;
            }}
             if(this.getIcon().equals("/images/kevin-diamant-3.png")){
                        return;
             }else{
                this.setIcon("/images/kevin-diamant-3.png");
             }
            }

        if(this.getCurrentCell().getLeftNeighbor()==null) {
            if (this.getIcon().equals("/images/kevin-pioche-3.png")) {
                return;
            }
            if (this.getIcon().equals("/images/kevin-pioche-1.png")) {
                this.setIcon("/images/kevin-pioche-3.png");
                return;
            }
            if (this.getIcon().equals("/images/kevin-diamant-3.png")) {
                return;
            }
            if (this.getIcon().equals("/images/kevin-diamant-1.png")) {
                this.setIcon("/images/kevin-diamant-3.png");
                return;
            }
        }
        if(this.getCurrentCell().getLeftNeighbor()!=null&&this.getCurrentCell().getLeftNeighbor().equals(c)){
            if(this.getIcon().equals("/images/kevin-pioche-1.png")){
                return;
            }else{
            if(this.getIcon().equals("/images/kevin-pioche.png")
                    ||this.getIcon().equals("/images/kevin-pioche-2.png")
                    ||this.getIcon().equals("/images/kevin-pioche-3.png")) {
                this.setIcon("/images/kevin-pioche-1.png");
                return;
            }}
            if(this.getIcon().equals("/images/kevin-diamant-1.png")){
                return;
            }else{
                this.setIcon("/images/kevin-diamant-1.png");
                return;
            }
        }

        if(this.getCurrentCell().getTopNeighbor()==null){
            if(this.getIcon().equals("/images/kevin-pioche.png")){
                return;
            }
            if(this.getIcon().equals("/images/kevin-pioche-2.png")){
                this.setIcon("/images/kevin-pioche.png");
                return;
            }
            if(this.getIcon().equals("/images/kevin-diamant.png")){
                return;
            }
            if(this.getIcon().equals("/images/kevin-diamant-2.png")){
                this.setIcon("/images/kevin-diamant.png");
                return;
            }
        }
        if(this.getCurrentCell().getTopNeighbor()!=null&&this.getCurrentCell().getTopNeighbor().equals(c)){
            if(this.getIcon().equals("/images/kevin-pioche-2.png")){
                return;
            }else{
                if(this.getIcon().equals("/images/kevin-pioche.png")
                        ||this.getIcon().equals("/images/kevin-pioche-1.png")
                        ||this.getIcon().equals("/images/kevin-pioche-3.png")){
                    this.setIcon("/images/kevin-pioche-2.png");
                    return;
                }}
            if(this.getIcon().equals("/images/kevin-diamant-2.png")){
                return;
            }else{
                this.setIcon("/images/kevin-diamant-2.png");
            }
        }

        if(this.getCurrentCell().getBottomNeighbor()==null){
            if(this.getIcon().equals("/images/kevin-pioche-2.png")){
                return;
            }
            if(this.getIcon().equals("/images/kevin-pioche.png")){
                this.setIcon("/images/kevin-pioche-2.png");
                return;
            }
            if(this.getIcon().equals("/images/kevin-diamant-2.png")){
                return;
            }
            if(this.getIcon().equals("/images/kevin-diamant.png")){
                this.setIcon("/images/kevin-diamant-2.png");
                return;
            }
        }
        if(this.getCurrentCell().getBottomNeighbor()!=null&&this.getCurrentCell().getBottomNeighbor().equals(c)){
            if(this.getIcon().equals("/images/kevin-pioche.png")){
                return;
            }else{
                if(this.getIcon().equals("/images/kevin-pioche-1.png")
                        ||this.getIcon().equals("/images/kevin-pioche-2.png")
                        ||this.getIcon().equals("/images/kevin-pioche-3.png")){
                    this.setIcon("/images/kevin-pioche.png");
                    return;
                }}
            if(this.getIcon().equals("/images/kevin-diamant.png")){
                return;
            }else{
                this.setIcon("/images/kevin-diamant.png");
            }
        }
    }

    /* Première méthode utilisée par les fourmis */
    @Override
    public void onStart() {
        setLocation(this.queen.getCurrentCell()); //spawn sur la reine
        setCurrentCell(this.queen.getCurrentCell());
        setSensingRange(34.0);
        this.createPheroTunnel = 0;
        this.opposedDirection = 2;
        this.currentDirection = 3;
        this.pathChoice();
    }


    /* Méthode permettant de choisir l'endroit où creuser un tunnel
    * */
    public void pathChoice() {
        List<PheroNode> lc = new ArrayList<PheroNode>();
        List<Node> l = this.getSensedNodes();
        int pheroCount = 0;
        CellLocatedNode tmp = null;
        for(Node node : l) { //Compte le nombre de phéromone autour
            CellLocatedNode n = (CellLocatedNode)node;
            if(n instanceof PheroNode && ((PheroNode)n).isTunnelPhero()) {
                lc.add(((PheroNode)n));
                pheroCount++;
                tmp = n;
            }
        }
        /* Cette partie du code permet de combiner les pheromones tunnel posées par les fourmis
        * A chaque entrée de tunnel si plusieurs fourmis entre en même temps il y aura autant de pheromone
        * tunnels à l'entrée que de fourmis dedans
        * Ainsi, il faut les combiner en une seule pheromone */
        List<PheroNode> lf = new ArrayList<PheroNode>();
        if(pheroCount>=2){ //Fusionne s'il y a des phéromones au même endroit
            for(PheroNode pheroNode : lc){
                if(lf.isEmpty()) {
                    lf.add(pheroNode);
                }else{
                    if(pheroNode.getCurrentCell().equals(lf.get(0).getCurrentCell())){
                        //Fusionner
                        double q1 = pheroNode.getQuantity();
                        while (q1 > 0) {
                            q1 = q1 - 0.1;
                            lf.get(0).incrementQuantity();
                        }
                        pheroNode.die();
                        pheroCount--;
                    }else{
                        if(lf.size()==1){
                            lf.add(pheroNode);
                        }else{ // On suppose qu'il y a que 2 positions possibles pour des phéronodes TUNNEL
                            //Fusionner
                            double q2 = pheroNode.getQuantity();
                            while (q2 > 0) {
                                q2 = q2 - 0.1;
                                lf.get(1).incrementQuantity();
                            }
                            pheroNode.die();
                            pheroCount--;
                        }
                    }
                }
            }
        }

        //si aucun tunnel occupe OU un tunnel occupe a DROITE
        if (pheroCount == 0 || (pheroCount == 1 && tmp.getCurrentCell().equals(this.getCurrentCell().getRightNeighbor()))) {
            Cell nextCell = this.getCurrentCell().getLeftNeighbor();
            this.addDestination(nextCell);
            this.createPheroTunnel = 1;
            this.currentDirection = 1;
            this.opposedDirection = 0;
            return;
        }
        // si un tunnel est occupe a GAUCHE
        if (pheroCount == 1 && tmp.getCurrentCell().equals(this.getCurrentCell().getLeftNeighbor())) {
            Cell nextCell = this.getCurrentCell().getRightNeighbor();
            this.addDestination(nextCell);
            this.createPheroTunnel = 1;
            this.currentDirection = 0;
            this.opposedDirection = 1;
            return;
        }
        // sinon les deux tunnels sont occupés
        if (pheroCount >= 2) {
            this.minecraftForTheWin();
            return;
        }
    }


    /* Méthode faisant avancer une fourmis 3 fois dans une meme direction (si possible) */
    public void minecraftForTheWin() {
        Cell next = this.getCurrentCell().getNeighBor(this.currentDirection);
        if(next==null){
            int tmp;
            tmp = this.currentDirection;
            this.currentDirection = this.opposedDirection;
            this.opposedDirection = tmp;
            pathChoice();
            return;
        }

        Cell nextOfNext = next.getNeighBor(this.currentDirection);
        if(nextOfNext==null){
            int tmp;
            tmp = this.currentDirection;
            this.currentDirection = this.opposedDirection;
            this.opposedDirection = tmp;
            pathChoice();
            return;
        }
        this.addDestination(next);
        this.addDestination(nextOfNext);

        Cell nextOfNextOfNext = nextOfNext.getNeighBor(this.currentDirection);
        if(nextOfNextOfNext==null){
            return;
        }
        this.addDestination(nextOfNextOfNext);
    }

    public void createPhero(Cell c,int type) { // Créer une pheromone et la place sur la cellule donnée
        PheroNode p = new PheroNode(type);
        p.setCurrentCell(c);
        p.setLocation(c);
        getTopology().addNode(p);
    }

    /* Dépot de nourriture dans la colonne principale */
    public void foodNodeDeposit() {
        List<Node> sensedList = this.getSensedNodes();
        // on regarde s'il existe une pheromone queen pour notre depot de nourriture, si oui on l'incrémente
        for(Node node : sensedList) {
            CellLocatedNode n = (CellLocatedNode) node;
            if (n instanceof PheroNode) {
                PheroNode p = (PheroNode) n;
                if(p.isQueenPhero()) {
                    p.incrementQuantity();
                }
            }
        }
        // on regarde s'il existe deja un depot de nourriture dans la colonne principale
        for(Node node : sensedList) {
            CellLocatedNode n = (CellLocatedNode)node;
            if (n.getCurrentCell().equals(this.getCurrentCell().getNeighBor(this.opposedDirection)) && n instanceof FoodNode) {
                ((FoodNode)n).incrementQuantity();
                ((FoodNode)n).setIconSize(((FoodNode)n).getQuantity() + 1);
                diamantToPioche();
                // on retourne dans notre tunnel
                Cell next = this.getCurrentCell().getNeighBor(this.opposedDirection);
                this.addDestination(next);
                return;
            }
        }
        // on créer une phéromone pour ne pas prendre ensuite la nourriture destiné à la reine
        this.createPhero(this.getCurrentCell().getNeighBor(this.opposedDirection),1);
        // si on arrive ici, il faut creer un depot de nourriture
        FoodNode f = new FoodNode();
        f.setQuantity(1);
        f.setIcon("/images/diamant.png");
        f.setIconSize(f.getQuantity());
        f.setCurrentCell(this.getCurrentCell().getNeighBor(this.opposedDirection));
        f.setLocation(this.getCurrentCell().getNeighBor(this.opposedDirection));
        getTopology().addNode(f);
        diamantToPioche();

        // on retourne dans notre tunnel
        Cell next = this.getCurrentCell().getNeighBor(this.currentDirection);
        this.addDestination(next);
    }

    /* Méthode onClock usuelle de WaypointNode */
    @Override
    public void onClock() {
        this.isDead(); // On regarde si la fourmi doit mourir à ce tour ou pas
        if ( ! destinations.isEmpty() ) { // On regarde s'il y a une destination
            Cell dest = destinations.peek();
            if (dest.getCost() > dest.getMinCostValue()) { // On regarde si on doit ne peut pas avancer et qu'on doit creuser le bloc pour en faire un tunnel
                dest.decrementCost();
            } else {
                if (distance(dest) > speed) {  // Si on n'est pas assez proche on avance vers la case
                    setDirection(dest);
                    move(speed);
                } else { // Sinon on se téléporte dessus
                    setLocation(dest);
                    onArrival(destinations.poll());
                }
            }
        }
    }

    /* Check si la fourmi est encore vivante */
    protected void isDead() {
        if(this.survivalTime-- <= 0) {
            if(this.getIcon().equals("/images/kevin-diamant.png")
                    ||this.getIcon().equals("/images/kevin-diamant-1.png")
                    ||this.getIcon().equals("/images/kevin-diamant-2.png")
                    ||this.getIcon().equals("/images/kevin-diamant-3.png")) {
                List<Node> sensedList = this.getSensedNodes();
                // on regarde s'il existe deja un depot de nourriture dans la colonne principale
                for (Node node : sensedList) {
                    CellLocatedNode n = (CellLocatedNode) node;
                    if (n instanceof FoodNode && n.getCurrentCell().equals(this.getCurrentCell())) {
                        ((FoodNode) n).incrementQuantity();
                        this.die();
                        return;
                    }
                }
                // si on arrive ici, il faut creer un depot de nourriture
                FoodNode f = new FoodNode();
                f.setQuantity(1);
                f.setIcon("/images/diamant.png");
                f.setIconSize(f.getQuantity());
                f.setCurrentCell(this.getCurrentCell());
                f.setLocation(this.getCurrentCell());
                getTopology().addNode(f);
            }
            this.die();
        }
    }

    /* Déplacement d'une fourmi d'un bloc */
    protected void antAlgorithm() {
        Cell cell = pickNeighBoringCell(); // choix destination
        this.addDestination(cell);
    }

    /* Plusieurs cas distingués à l'arrivée */
    @Override
    public void onArrival(Cell d) {
        this.lastCellMemory = this.getCurrentCell();
        this.setCurrentCell(d);
        // cas où la fourmi crée son tunnel
        if (this.createPheroTunnel == 1) {
            this.createPheroTunnel = 0;
            this.needTunnel = 0;
            this.createPhero(this.getCurrentCell(),0);
            this.addDestination(this.getCurrentCell().getNeighBor(this.currentDirection));
            return;
        }
        // Si la fourmi n'a pas trouvé de nourriture et qu'il a besoin d'un tunnel alors on relance l'algorithme pour créer des tunnels
        if (this.destinations.isEmpty() && this.needTunnel == 1 && this.beanSensed != 1 && (this.getIcon().equals("/images/kevin-pioche.png")
                ||this.getIcon().equals("/images/kevin-pioche-1.png")
                ||this.getIcon().equals("/images/kevin-pioche-2.png")
                ||this.getIcon().equals("/images/kevin-pioche-3.png"))) {
            this.pathChoice();
            return;
        }
        if (this.destinations.isEmpty()) {
            // cas où la fourmi n'a pas de nourriture
            if (! (this.getIcon().equals("/images/kevin-diamant.png")
                    ||this.getIcon().equals("/images/kevin-diamant-1.png")
                    ||this.getIcon().equals("/images/kevin-diamant-2.png")
                    ||this.getIcon().equals("/images/kevin-diamant-3.png"))) {
                if (this.beanSensed == 0 ) {
                    // aucune nourriture sentie
                    antAlgorithm();
                    return;
                }else{
                    // une nourriture a été sentie à l'étape n-1, et la fourmie est arrivée dessus
                    this.takeFood(this.nodeSensed);
                    return;
                }
            }
            // cas où la fourmi a déjà de la nourriture et n'a pas de tunnel
            if ((this.getIcon().equals("/images/kevin-diamant.png")
                    ||this.getIcon().equals("/images/kevin-diamant-1.png")
                    ||this.getIcon().equals("/images/kevin-diamant-2.png")
                    ||this.getIcon().equals("/images/kevin-diamant-3.png")) && this.needTunnel == 1) {
                if (d == this.queen.getCurrentCell()) {
                    dropFood();
                    this.pathChoice();
                }else{
                    this.backToQueen();
                }
                return;
            }
            if ((this.getIcon().equals("/images/kevin-diamant.png") // Si la fourmi est dans un tunnel et qu'il a un diamant alors il continue d'avancer jusqu'à atteindre la phéromone
                    ||this.getIcon().equals("/images/kevin-diamant-1.png")
                    ||this.getIcon().equals("/images/kevin-diamant-2.png")
                    ||this.getIcon().equals("/images/kevin-diamant-3.png")) && this.needTunnel == 0) {
                this.antAlgorithm();
                return;
            }
        }
    }

    /* Méthode de retour d'une fourmi à la reine */
    protected void backToQueen() {
        this.destinations.clear();
        this.addDestination(this.queen.getCurrentCell());
    }

    protected void backToMiddle() { // Retourne à la case d'où il a détecter la nourriture puis retourne jusqu'à la pheronome tunnel à l'entrée du tunnel
        this.destinations.clear();
        int tmp = this.currentDirection;
        this.currentDirection = this.opposedDirection;
        this.opposedDirection = tmp;
        if(this.lastCellMemory.equals(this.getCurrentCell().getTopLeftNeighbor())||this.lastCellMemory.equals(this.getCurrentCell().getTopRightNeighbor())){ // Si on a détecter en diagonale alors on retourne en prennant bien l'angle droit
            this.addDestination(this.getCurrentCell().getTopNeighbor());
            this.addDestination(this.lastCellMemory);
            return;
        }else{
            if(this.lastCellMemory.equals(this.getCurrentCell().getBottomLeftNeighbor())||this.lastCellMemory.equals(this.getCurrentCell().getBottomRightNeighbor())){ // Si on a détecter en diagonale alors on retourne en prennant bien l'angle droit
                this.addDestination(this.getCurrentCell().getBottomNeighbor());
                this.addDestination(this.lastCellMemory);
                return;
            }else{
                this.addDestination(this.lastCellMemory);
                return;
            }
        }
    }


    /* Méthode donnant la prochaine destination d'une fourmi en regardant si elle a atteint un bord de carte */
    protected Cell pickNeighBoringCell() {
        int tmp;
        Cell nextCell = null;
        // cas où la fourmi est affectée à un tunnel
        if (this.needTunnel == 0 ) {
            CellLocatedNode tmpnode = null;
            List<Node> l = getSensedNodes();
            for(Node node : l) {
                CellLocatedNode n = (CellLocatedNode)node;
                if(n instanceof PheroNode && ((PheroNode)n).isTunnelPhero()) {
                    tmpnode = n;
                }
            }
            if (tmpnode != null && this.getCurrentCell().equals(tmpnode.getCurrentCell())) {
                if(! this.lastCellMemory.equals(tmpnode.getCurrentCell())) {
                    tmp = this.currentDirection;
                    this.currentDirection = this.opposedDirection;
                    this.opposedDirection = tmp;
                }
                ((PheroNode)tmpnode).incrementQuantity();
                if ((this.getIcon().equals("/images/kevin-diamant.png")
                        ||this.getIcon().equals("/images/kevin-diamant-1.png")
                        ||this.getIcon().equals("/images/kevin-diamant-2.png")
                        ||this.getIcon().equals("/images/kevin-diamant-3.png"))) {
                    this.foodNodeDeposit();
                }
            }
        }
        nextCell = getCurrentCell().getNeighBor(this.currentDirection);
        if (nextCell == null) {
            // si on atteint un bord de carte
            tmp = this.currentDirection;
            this.currentDirection = this.opposedDirection;
            this.opposedDirection = tmp;
            nextCell = getCurrentCell().getNeighBor(this.currentDirection);
        }
        return nextCell;
    }

    /* Détection de nourriture  */
    @Override
    public void onSensingIn(Node n) { // Permet de sentir la nourriture et se déplacer vers
        List<Node> sensedList = this.getSensedNodes();
        if(n instanceof FoodNode && (! (this.getIcon().equals("/images/kevin-diamant.png")
                ||this.getIcon().equals("/images/kevin-diamant-1.png")
                ||this.getIcon().equals("/images/kevin-diamant-2.png")
                ||this.getIcon().equals("/images/kevin-diamant-3.png"))) && beanSensed != 1) {
            if(this.needTunnel==0) {
                // on regarde s'il existe deja un depot de nourriture dans la colonne principale
                for (Node node : sensedList) {
                    CellLocatedNode cn = (CellLocatedNode) node;
                    if (cn instanceof PheroNode) {
                        PheroNode p = (PheroNode) cn;
                        if(this.getCurrentCell().equals(p.getCurrentCell())){
                            return;
                        }
                        if(this.lastCellMemory.equals(p.getCurrentCell())){
                            return;
                        }
                        if (p.isQueenPhero() && p.getCurrentCell().equals(((CellLocatedNode) n).getCurrentCell())) {
                            return;
                        }
                    }
                }
            }
            // empeche les fourmis devant déposer une pheromone tunnel de ramasser de la nourriture
            if(this.createPheroTunnel==1){
                return;
            }
            this.beanSensed = 1;
            this.destinations.clear();
            this.addDestination(((FoodNode) n).getCurrentCell());
            this.nodeSensed = (FoodNode) n;
        }
    }

    /* Récupération de nourriture */
    public void takeFood(FoodNode f) {
        int q = f.getQuantity();
        f.setQuantity(q-1);
        piocheToDiamant();
        this.beanSensed = 0;
        // action à faire après avoir récupéré la nourriture
        if(this.needTunnel == 1) {
            backToQueen();
        }else{
            backToMiddle();
        }
    }

    /* Dépot de nourriture sur la reine */
    public void dropFood() {
        diamantToPioche();
        this.queen.incrementFoodStock();
    }

    /* Affichage */
    public void piocheToDiamant() {
        if (this.getDirection()==0) {
            this.setIcon("/images/kevin-diamant-3.png");
        } else {
            if (this.getDirection()==1) {
                this.setIcon("/images/kevin-diamant-1.png");
            } else {
                if (this.getDirection()==2) {
                    this.setIcon("/images/kevin-diamant-2.png");
                } else {
                    this.setIcon("/images/kevin-diamant.png");
                }
            }
        }
    }

    /* Affichage */
    public void diamantToPioche() {
        if(this.getDirection()==0){
            this.setIcon("/images/kevin-pioche-3.png");
        }else{
            if(this.getDirection()==1){
                this.setIcon("/images/kevin-pioche-1.png");
            }else{
                if(this.getDirection()==2){
                    this.setIcon("/images/kevin-pioche-2.png");
                }else{
                    this.setIcon("/images/kevin-pioche.png");
                }
            }
        }
    }

    /* Débug */
    @Override
    public String toString(){
        return "Vie restante" + this.survivalTime;
    }

}
