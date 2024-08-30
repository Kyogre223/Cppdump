//
// Created by Lin Kai on 31/8/24.
//


class MyCircularQueue {
public:
    int* ptr_ = nullptr;
    // local buffer optimisation
    int buf_[16];
    int write = 0;
    int read = 0;
    int capacity = 0;
    int size = 0;
    MyCircularQueue(int k) {
        if (k > 16) {
            ptr_ = new int[k];
            this->capacity = k;
            for (int i = 0; i < k; ++i) ptr_[i] = -1;
        } else {
            ptr_ = buf_;
            for (int i = 0; i < 16; ++i) {
                ptr_[i] = -1;
            }
            this->capacity = k;

        }
    }

    bool enQueue(int value) { //write
        if (this->size == capacity) return false;
        this->size++;
        ptr_[write] = value;
        ++write;
        write %= capacity;
        return true;
    }

    bool deQueue() { // read
        if (this->size == 0) return false;
        this->size--;
        ptr_[read] = -1;
        ++read;
        read %= capacity;
        return true;

    }

    int Front() { //read
        if (this->size == 0) return -1;
        return ptr_[read];
    }

    int Rear() { //write
        if (this->size == 0) return -1;

        return ptr_[(write - 1 + capacity) % capacity];

    }

    bool isEmpty() {
        return this->size == 0;
    }

    bool isFull() {
        return this->size == capacity;
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */
