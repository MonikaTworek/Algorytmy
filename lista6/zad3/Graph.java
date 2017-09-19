package zad3;

import zad1.PriorityQueue;
import zad1.QueueElement;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class Graph {
    private List<GraphVertex> vertexList;
    private List<GraphEdge> edges;

    public Graph(String path) {
        final List<String> list;

        try (BufferedReader br = Files.newBufferedReader(Paths.get(path))) {
            list = br.lines().collect(Collectors.toList());
            vertexList = new ArrayList<>();
            edges = new ArrayList<>();
            int vertexesCount = Integer.parseInt(list.get(0));
            IntStream.rangeClosed(0,vertexesCount).forEach(i -> vertexList.add(new GraphVertex(i)));
            IntStream.range(2, list.size()).forEach(i->{
                String line = list.get(i);
                String[] data = line.split(" ");
                GraphEdge toAdd = new GraphEdge(vertexList.get(Integer.parseInt(data[0])), vertexList.get(Integer.parseInt(data[1])),Double.parseDouble(data[2]));
                edges.add(toAdd);
                vertexList.get(Integer.parseInt(data[0])).addEdge(toAdd);
            });
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public List<GraphEdge> getEdges() {
        return edges;
    }

    public void dijkstraShortestPaths(int vertex) {
        PriorityQueue<GraphVertex> priorityQueue = new PriorityQueue<>();
        vertexList.forEach(v->{
            if(v.getId()==vertex) {
                v.setDistance(0);
            }
            priorityQueue.insert(v.getDistance(), v);
        });

        while (priorityQueue.getQueueSize() > 0) {
            QueueElement<GraphVertex> element = priorityQueue.extractMin();
            GraphVertex current = element.getData();
            current.getEdges().forEach(edge -> {
                if (edge.getTo().getDistance() > current.getDistance() + edge.getWeight()) {
                    edge.getTo().setDistance(current.getDistance()+edge.getWeight());
                    edge.getTo().setPredecessor(current);
                    priorityQueue.updateKey(edge.getTo().getPositionInQueue(),edge.getTo().getPositionInQueue()-1);
                }
            });
        }
    }

    public GraphVertex dijkstraShortestPathsTo(int vertex, int to) {
        GraphVertex result = null;
        PriorityQueue<GraphVertex> priorityQueue = new PriorityQueue<>();
        vertexList.forEach(v->{
            if(v.getId()==vertex) {
                v.setDistance(0);
            }
            priorityQueue.insert(v.getDistance(), v);
        });

        while (priorityQueue.getQueueSize() > 0) {
            QueueElement<GraphVertex> element = priorityQueue.extractMin();
            if (element.getData().getId() == to)
                result = element.getData();
            GraphVertex current = element.getData();
            current.getEdges().forEach(edge -> {
                if (edge.getTo().getDistance() > current.getDistance() + edge.getWeight()) {
                    edge.getTo().setDistance(current.getDistance()+edge.getWeight());
                    edge.getTo().setPredecessor(current);
                    priorityQueue.updateKey(edge.getTo().getPositionInQueue(),edge.getTo().getDistance());
                }
            });
        }
        if(result == null || result.getPredecessor()==null)
            throw new RuntimeException("Can't find any path");
        return result;
    }

    public void getDijkstraPath(int from, int to) {
        GraphVertex dest = this.dijkstraShortestPathsTo(from, to);
        GraphVertex prev = dest.getPredecessor();
        System.out.println("From: " + from + " To: " + to + " Cost: " + dest.getDistance());
        System.out.print(dest.getId() + "(" + (dest.getDistance() - prev.getDistance()) + ")");
        while (prev != null) {
            if(prev.getPredecessor() != null)
                System.out.print(" <--- " +prev.getId() + "(" + (prev.getDistance() - prev.getPredecessor().getDistance()) + ")");
            else {
                System.out.print(" <--- " + prev.getId() + "(");
                System.out.format("%.2f", prev.getDistance());
                System.out.print(")");
            }
            prev = prev.getPredecessor();
        }
    }

    public List<GraphVertex> getVertexList() {
        return vertexList;
    }
}