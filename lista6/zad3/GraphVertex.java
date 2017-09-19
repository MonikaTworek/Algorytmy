package zad3;

import zad1.Queuable;
import java.util.ArrayList;
import java.util.List;

public class GraphVertex implements Queuable {
    private int id;
    private List<GraphEdge> edges;
    private GraphVertex predecessor;
    private double distance;
    private int positionInQueue;
    private GraphVertex parent;
    private int rank;
    private GraphEdge primEdge;
    private Boolean inQ = true;

    public GraphEdge getPrimEdge() {
        return primEdge;
    }

    public void setPrimEdge(GraphEdge primEdge) {
        this.primEdge = primEdge;
    }

    public int getRank() {
        return rank;
    }

    public void setRank(int rank) {
        this.rank = rank;
    }

    public GraphVertex getParent() {
        return parent;
    }

    public void setParent(GraphVertex parent) {
        this.parent = parent;
    }

    public GraphVertex(int id) {
        this.id = id;
        this.edges = new ArrayList<>();
        this.predecessor = null;
        this.distance = Double.MAX_VALUE;
    }

    public int getPositionInQueue() {
        return positionInQueue;
    }

    public void setPositionInQueue(int positionInQueue) {
        this.positionInQueue = positionInQueue;
    }

    @Override
    public boolean inQ() {
        return inQ;
    }

    @Override
    public void setInQ(boolean inQ) {
        this.inQ = inQ;
    }

    public GraphVertex getPredecessor() {
        return predecessor;
    }

    public void setPredecessor(GraphVertex predecessor) {
        this.predecessor = predecessor;
    }

    public double getDistance() {
        return distance;
    }

    public void setDistance(double distance) {
        this.distance = distance;
    }

    public void addEdge(GraphEdge edge) {
        edges.add(edge);
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public List<GraphEdge> getEdges() {
        return edges;
    }

    public void setEdges(List<GraphEdge> edges) {
        this.edges = edges;
    }
}
