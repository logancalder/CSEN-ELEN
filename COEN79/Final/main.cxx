#include <vector>

template <typename T>
class RingBuffer {
private:
    std::vector<T> buffer;  // Use std::vector for dynamic storage

    size_t capacity;
    size_t front;

public:
    // Constructor
    RingBuffer(size_t capacity) : buffer(capacity), capacity(capacity), front(0) {}

    // Member function to insert a new record
    void insert(const T& record) {
        if (buffer.size() == capacity) {
            // Remove the oldest record by erasing the element at the front
            buffer.erase(buffer.begin());
        }

        // Insert the new record at the back
        buffer.push_back(record);
    }
};
