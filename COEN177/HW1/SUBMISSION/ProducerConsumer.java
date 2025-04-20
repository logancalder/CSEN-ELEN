// # Name: Logan Calder
// # Date: 12/04/2024
// # Title: Homework 1
// # Description: This file is the producer consumer problem using a circular buffer with a lock and condition variables
// #
// # Usage: javac ProducerConsumer.java; java ProducerConsumer <consumer_count> <producer_count>


import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ProducerConsumer {

    private static class CircularBuffer {

        private final int[] buffer;
        private int capacity;
        private int size = 0;
        private int write = 0;
        private int readPos = 0;
        private final Lock lock = new ReentrantLock();
        private final Condition isFull = lock.newCondition();
        private final Condition isEmpty = lock.newCondition();

        public CircularBuffer(int capacity) {
            this.capacity = capacity;
            this.buffer = new int[capacity];
        }

        public void add(int value) throws InterruptedException {
            lock.lock();
            try {
                while (size == capacity) {
                    isFull.await();
                }
                buffer[write] = value;
                write = (write + 1) % capacity;
                size++;
                isEmpty.signalAll();
            } finally {
                lock.unlock();
            }
        }

        public int remove() throws InterruptedException {
            lock.lock();
            try {
                while (size == 0) {
                    isEmpty.await();
                }
                int value = buffer[readPos];
                readPos = (readPos + 1) % capacity;
                size--;
                isFull.signalAll();
                return value;
            } finally {
                lock.unlock();
            }
        }
    }

    // producer function as new entry point function
    public static int producer(CircularBuffer buffer, int maxItems) {
        try {
            for (int i = 0; i < maxItems; i++) {
                buffer.add(i);
                System.out.println("produced " + i);
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            System.err.println("producer interrupted");
        }
        return 0;
    }

    // Consumer function as new entry point function
    public static int consumer(CircularBuffer buffer) {
        try {
            while (true) {
                int value = buffer.remove();
                System.out.println(Thread.currentThread().getName() + " consumed " + value);
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            System.err.println(Thread.currentThread().getName() + " interrupted");
        }
        return 0;
    }

    public static void main(String[] args) {
        if (args.length != 2) {
            return;
        }

        int consumer_count;
        int max;

        consumer_count = Integer.parseInt(args[0]);
        max = Integer.parseInt(args[1]); // instructions were unclear so I have two args in cmd line, read the README.md for more details

        int bufferSize = 10;
        int maxItems = max;

        CircularBuffer buffer = new CircularBuffer(bufferSize);

        long start = System.nanoTime();
        Thread producer = new Thread(() -> producer(buffer, maxItems));
        producer.start();

        // Consumer threads as new entry point functions
        Thread[] consumer_threads = new Thread[consumer_count];
        for (int i = 0; i < consumer_count; i++) {
            consumer_threads[i] = new Thread(() -> consumer(buffer), "consumed " + (i + 1));
            consumer_threads[i].start();
        }

        try {
            producer.join();
            for (Thread consumer : consumer_threads) {
                consumer.interrupt();
            }
            for (Thread consumer : consumer_threads) {
                consumer.join();
            }
        } catch (InterruptedException e) {
            System.err.println("interrupt");
        }

        // Record end time
        long end = System.nanoTime();
        long duration = end - start;

        System.out.println("total program execution time " + duration + "ns");
    }
}
