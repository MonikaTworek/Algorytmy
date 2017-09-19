package zad3;

public class GraphEdge implements Comparable<GraphEdge> {
    private GraphVertex from;
    private GraphVertex to;
    private double weight;

    public GraphEdge(GraphVertex from, GraphVertex to, double weight) {
        this.from = from;
        this.to = to;
        this.weight = weight;
    }

    public GraphVertex getFrom() {
        return from;
    }

    public GraphVertex getTo() {
        return to;
    }

    public double getWeight() {
        return weight;
    }

    @Override
    public int compareTo(GraphEdge graphEdge) {
        if(this.getWeight()==graphEdge.getWeight())
            return 0;
        else if (this.getWeight()>graphEdge.getWeight())
            return 1;
        else
            return -1;
//        return (int)(this.getWeight() - graphEdge.getWeight() );
    }
}
