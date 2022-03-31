import java.io.*;
import java.lang.*;

public class Buffer {

    private int capacity = 0; // initial capacity of buffer
    private int size = 0; //initial size of buffer
    private int head = 0; //head pointer
    private int tail = -1; //tail pointer
    private Object[] array;

    //Constructor
    Buffer(int capacity) {
        this.capacity = capacity;
        array = new Object[capacity];
    }
    
    //Add element
    public void add(Object element) {

        int index = (tail + 1) % capacity;
        size++;

        if (size == capacity) {
            System.out.println("Buffer Overflow!!!");
        }

        array[index] = element;
        tail ++;
    }

    //Delete element
    public Object get() {

        if(size == 0) {
            System.out.println("Empty Buffer");
            return 0;
        }

        int index = head % capacity;
        Object element = array[index];
        head++;
        size--;
        return element;
    }

    public Object peek() {
        if (size == 0) {
            System.out.println("Empty Buffer");
        }

        int index = head % capacity;
        Object element = array[index];
        return element;
    }

    public boolean isEmpty () {
        return size == 0;
    }

    public int capacity () {
        return capacity;
    }

    public int size () {
        return size;
    }
}
