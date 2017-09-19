package zad3;

public class Main {
    public static void main(String[] args) {
        int from = 0;
        int to = 6;
        Graph graph = new Graph("C:\\Users\\Mona\\Desktop\\aisd\\lista6\\data.txt");
        graph.getDijkstraPath(from,to);
    }
}
