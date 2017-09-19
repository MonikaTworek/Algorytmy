package zad2;

import zad1.PriorityQueue;
import zad1.QueueElement;
import zad3.Graph;
import zad3.GraphEdge;
import zad3.GraphVertex;

import java.util.ArrayList;

public class Prim {
    private Graph graph;

    public Prim(String path) {
        this.graph = new Graph(path);
    }

    public void prim(int vertex) {
        PriorityQueue<GraphVertex> priorityQueue = new PriorityQueue<>();
        graph.getVertexList().forEach(v->{
            if(v.getId()==vertex) {
                v.setDistance(0);
            }
            priorityQueue.insert(v.getDistance(), v);
        });

        while (priorityQueue.getQueueSize() > 0) {
            QueueElement<GraphVertex> element = priorityQueue.extractMin();
            element.getData().setInQ(false);
            GraphVertex current = element.getData();
            current.getEdges().forEach(edge -> {
                if (edge.getTo().getDistance() > edge.getWeight() && edge.getTo().inQ()) {
                    edge.getTo().setDistance(edge.getWeight());
                    edge.getTo().setPredecessor(current);
                    edge.getTo().setPrimEdge(edge);
                    priorityQueue.updateKey(edge.getTo().getPositionInQueue(), edge.getTo().getDistance());
                }
            });
        }
    }
    public ArrayList<GraphEdge> getMST() {
        ArrayList<GraphEdge> mst = new ArrayList<>();
        graph.getVertexList().stream().filter(v->v.getPrimEdge()!=null).forEach(v->mst.add(v.getPrimEdge()));
        mst.forEach(e->System.out.println(e.getFrom().getId() + " -> " + e.getTo().getId()));
        return mst;
    }
}
