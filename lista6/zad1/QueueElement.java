package zad1;

public class QueueElement<T extends Queuable> {
    private T data;
    private double priority;

    public QueueElement(T data, double priority) {
        this.data = data;
        this.priority = priority;
    }

    public T getData() {
        return data;
    }

    public void setData(T data) {
        this.data = data;
    }

    public double getPriority() {
        return priority;
    }

    public void setPriority(double priority) {
        this.priority = priority;
    }
}
