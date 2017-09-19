package zad2;

public class Main {
    public static void main(String[] args) {
        System.out.println("KRUSKAL: ");
        Kruskal k = new Kruskal("C:\\Users\\Mona\\Desktop\\aisd\\lista6\\dataKruskal.txt");
        k.showMST();
        Prim p = new Prim("C:\\Users\\Mona\\Desktop\\aisd\\lista6\\data.txt");
        System.out.println("PRIM: ");
        p.prim(1);
        p.getMST();
    }

}
