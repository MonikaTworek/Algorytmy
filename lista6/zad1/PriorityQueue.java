package zad1;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class PriorityQueue<T extends Queuable> {
    private List<QueueElement<T>> nodes;

    public PriorityQueue() {
        nodes = new ArrayList<>();
    }

    public void insert(double priority, T value) {
        int iterator = nodes.size();
        nodes.add(new QueueElement<>(value, 0));
        nodes.get(nodes.size() - 1).getData().setPositionInQueue(nodes.size() - 1);
        while (iterator > 0 && nodes.get(getParent(iterator)).getPriority() > priority) {
            nodes.set(iterator, nodes.get(getParent(iterator)));
            nodes.get(iterator).getData().setPositionInQueue(iterator);
            iterator = getParent(iterator);
        }
        nodes.set(iterator, new QueueElement<>(value, priority));
        nodes.get(iterator).getData().setPositionInQueue(iterator);
    }
    
    public void updateKey(int index, double newPriority) {
        if(nodes.get(index).getPriority() < newPriority) {
            nodes.get(index).setPriority(newPriority);
            heapify(index);
        }
        else {
            nodes.get(index).setPriority(newPriority);
            int iterator = index;
            while (iterator > 0 && nodes.get(getParent(iterator)).getPriority() > newPriority) {
                swap(iterator, getParent(iterator));
                iterator = getParent(iterator);
            }
        }
    }
    
    public QueueElement<T> extractMin() {
        QueueElement<T> result = nodes.get(0);
        swap(0, nodes.size()-1);
        nodes.remove(nodes.size()-1);
        heapify(0);
        return result;
    }

    public int getQueueSize() {
        return nodes.size();
    }

    private void swap(int a, int b) {
        int helperPos = nodes.get(a).getData().getPositionInQueue();
        nodes.get(a).getData().setPositionInQueue(nodes.get(b).getData().getPositionInQueue());
        nodes.get(b).getData().setPositionInQueue(helperPos);
        Collections.swap(nodes, a, b);
    }

    private int getParent(int index) {
        return (int) (Math.ceil(((double) index)/2)-1);
    }
    
    private int getLeft(int index) {
        return index * 2 + 1;
    }
    
    private int getRight(int index) {
        return  index * 2 + 2;
    }
    
    private void heapify(int index) {
        int lowest;
        int indexLeft = getLeft(index);
        int indexRight = getRight(index);
        if (indexLeft < nodes.size() && nodes.get(indexLeft).getPriority() < nodes.get(index).getPriority())
            lowest = indexLeft;
        else
            lowest = index;
        if (indexRight < nodes.size() && nodes.get(indexRight).getPriority() < nodes.get(lowest).getPriority())
            lowest = indexRight;
        if (lowest != index){
            swap(index, lowest);
            heapify(lowest);
        }
    }
}
