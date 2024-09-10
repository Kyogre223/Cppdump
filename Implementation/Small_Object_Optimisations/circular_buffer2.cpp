class MyCircularQueue {
public:
    int* arr_;
    int r = 0; // always point at the valid one to read;
    int w = 0; // always point at the next empty;
    int size = 0;
    int capacity = 0;
    int buffer_[15]; // SBO 
    // we can further optimize the k, size.  can make it 2 ^ smth.

    MyCircularQueue(int k) {
        if (k <= 15 ) {
            arr_ = buffer_;
        } else {
            arr_ = new int[k];
        }
        capacity = k;
        size = 0;
        r = 0;
        w = 0;
    }

    bool enQueue(int value) {
        if (size == capacity) return false;
        arr_[w++] = value;
        ++size;
        w %= capacity;
        return true;
    }

    bool deQueue() {
        if (size == 0) return false;

        --size;
        ++r;
        r %= capacity;
        return true;
    }

    int Front() const {
        // read the reader
        if (size == 0) return -1;

        return arr_[r];
    }

    int Rear() const {
        // read the writer
        if (size == 0) return -1;
        return arr_[(w - 1 + capacity) % capacity];
    }

    bool isEmpty() const {
        return size == 0;
    }

    bool isFull() const {
        return size == capacity;
    }
};