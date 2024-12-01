
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ProducerConsumer {

    private static class CircularBuffer {

        private final int[] buffer;
        private int capacity;
        private int size = 0;
        private int writePos = 0;
        private int readPos = 0;

        private final Lock lock = new ReentrantLock();
        private final Condition notFull = lock.newCondition();
        private final Condition notEmpty = lock.newCondition();

        public CircularBuffer(int capacity) {
            this.capacity = capacity;
            this.buffer = new int[capacity];
        }

        public void add(int value) throws InterruptedException {
            lock.lock();
            try {
                while (size == capacity) {
                    notFull.await();
                }
                buffer[writePos] = value;
                writePos = (writePos + 1) % capacity;
                size++;
                notEmpty.signalAll();
            } finally {
                lock.unlock();
            }
        }

        public int remove() throws InterruptedException {
            lock.lock();
            try {
                while (size == 0) {
                    notEmpty.await();
                }
                int value = buffer[readPos];
                readPos = (readPos + 1) % capacity;
                size--;
                notFull.signalAll();
                return value;
            } finally {
                lock.unlock();
            }
        }
    }

    private static class Producer implements Runnable {

        private final CircularBuffer buffer;
        private final int maxItems;

        public Producer(CircularBuffer buffer, int maxItems) {
            this.buffer = buffer;
            this.maxItems = maxItems;
        }

        @Override
        public void run() {
            try {
                for (int i = 0; i < maxItems; i++) {
                    buffer.add(i);
                    System.out.println("Produced: " + i);
                }
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                System.err.println("Producer interrupted");
            }
        }
    }

    private static class Consumer implements Runnable {

        private final CircularBuffer buffer;

        public Consumer(CircularBuffer buffer) {
            this.buffer = buffer;
        }

        @Override
        public void run() {
            try {
                while (true) {
                    int value = buffer.remove();
                    System.out.println(Thread.currentThread().getName() + " Consumed: " + value);
                }
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                System.err.println(Thread.currentThread().getName() + " interrupted");
            }
        }
    }

    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Usage: java ProducerConsumer <number_of_consumers> <maximum>");
            return;
        }

        int numConsumers;
        int maximum;
        try {
            numConsumers = Integer.parseInt(args[0]);
            maximum = Integer.parseInt(args[1]);
        } catch (NumberFormatException e) {
            System.err.println("Invalid number of consumers");
            return;
        }

        int bufferSize = 10;
        int maxItems = maximum;

        CircularBuffer buffer = new CircularBuffer(bufferSize);

        Thread producerThread = new Thread(new Producer(buffer, maxItems));
        producerThread.start();

        Thread[] consumerThreads = new Thread[numConsumers];
        for (int i = 0; i < numConsumers; i++) {
            consumerThreads[i] = new Thread(new Consumer(buffer), "Consumer " + (i + 1));
            consumerThreads[i].start();
        }

        try {
            producerThread.join();
            for (Thread consumer : consumerThreads) {
                consumer.interrupt();
            }
            for (Thread consumer : consumerThreads) {
                consumer.join();
            }
        } catch (InterruptedException e) {
            System.err.println("Main thread interrupted");
        }

        System.out.println("All threads have completed execution");
    }
}
