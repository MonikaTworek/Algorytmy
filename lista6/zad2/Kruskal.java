package zad2;
import zad3.Graph;
import zad3.GraphEdge;
import zad3.GraphVertex;


import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Kruskal {
    private Graph graph;
    private List<GraphEdge> mst;

    public Kruskal(String path) {
        this.mst = new ArrayList<>();
        this.graph = new Graph(path);
        graph.getVertexList().forEach(this::makeSet);
        Collections.sort(graph.getEdges());
        graph.getEdges().forEach(graphEdge -> {
            if(!find(graphEdge.getFrom()).equals(find(graphEdge.getTo()))) {
                mst.add(graphEdge);
                union(graphEdge.getFrom(),graphEdge.getTo());
            }
        });
    }

    public void showMST() {
        mst.forEach(e->System.out.println(e.getFrom().getId() + " -> " + e.getTo().getId()));
    }

    private void makeSet(GraphVertex vertex) {
        vertex.setParent(vertex);
        vertex.setRank(0);
    }

    private GraphVertex find(GraphVertex vertex) {
        while(vertex != vertex.getParent()) {
            vertex = vertex.getParent();
        }
        return vertex;
    }

    private void union(GraphVertex vertexA, GraphVertex vertexB) {
        GraphVertex rootA = find(vertexA);
        GraphVertex rootB = find(vertexB);
        if (rootA.equals(rootB))
            return;
        if (rootA.getRank() > rootB.getRank() ) {
            rootB.setParent(rootA);
        }
        else {
            rootA.setParent(rootB);
            if (rootA.getRank() == rootB.getRank())
                rootB.setRank(rootB.getRank() + 1);
        }
    }
}
