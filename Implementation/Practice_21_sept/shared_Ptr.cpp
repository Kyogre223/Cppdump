//
// Created by Lin Kai on 21/9/24.
//


#include <iostream>
#include <memory>



// shared ptrs ?

template <typename T>
class Shared_Ptr {
    T* data_;
    int* ref_count_;
public:

    // constructor
    Shared_Ptr(T* data): data_(data) {
        ref_count_ = new int(1);
    }
    Shared_Ptr(){ref_count_ = new int(0);} // do nothing

    // copy constructor
    Shared_Ptr(Shared_Ptr const& other) {
        data_ = other.data_;
        ref_count_ = other.ref_count_;
        increment();
    }

    // copy assignment ?
    Shared_Ptr& operator = (Shared_Ptr const& other) {
        data_ = other.data_;
        ref_count_ = other.ref_count_;
        increment();
    }

    // move assignment constructor ?


    void increment() {
        (*ref_count_)++;
    }

    void decrement() {
        (*ref_count_)--;
        if (*ref_count_ == 0) delete ref_count_;
    }

    int use_count() const {
        return *ref_count_;
    }


    ~Shared_Ptr() {
        decrement();
    }
};


int main() {
    Shared_Ptr<int>ptr(new int(1));
    Shared_Ptr<int>ptr2 = ptr;
    std::cout << ptr2.use_count() << '\n';


    return 0;
}