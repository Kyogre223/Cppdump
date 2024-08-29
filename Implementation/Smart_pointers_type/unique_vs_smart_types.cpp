#include <iostream>
#include <memory>

template <typename T>
void f(T f ,T* ptr) {
    std::cout << "f(T, T*)\n";
}


struct MyHeap {

    void* allocate(int size) {
        return malloc(size);
    }

    void deallocate(void* p) {
        std::cout << "I have deallocated!\n";
        free(p);
    }
};

struct MyDelete {
    MyHeap* h_;
    MyDelete(MyHeap* ptr):h_(ptr){}
    template <typename T>
    void operator() (T* ptr) {
        ptr->~T();
        h_->deallocate(ptr);
    }
};


void* operator new (size_t size, MyHeap* ptr) {
    std::cout << "My heap called!\n";
    return ptr->allocate(size);
}


struct Obj {
    Obj() {
        std::cout << "Myobj\n";
    }
};





int main( ) {

    // std::shared_ptr<int>ptr = std::make_shared<int>();
    // std::shared_ptr<int>ptr2;
    // std::cout << ptr.use_count() << '\n';
    // std::cout << ptr2.use_count() << '\n';
    MyHeap heap;
    MyDelete deleter(&heap);
    std::unique_ptr<int, MyDelete>ptr (new (&heap) int(0), deleter);
    std::unique_ptr<int>ptr2;
    // if(std::is_same_v<decltype(ptr2), decltype(ptr)>) {
    //     std::cout << "SAME\n";
    // } else {
    //     std::cout << "DIFFERENT!\n";
    // }

    std::shared_ptr<int>shptr(new (&heap) int(0), deleter);
    std::shared_ptr<int>shptr2(new (&heap) int(0));
    shptr2 = std::move(shptr);
    if(std::is_same_v<decltype(shptr), decltype(shptr2)>) {
        std::cout << "SAME\n";
    } else {
        std::cout << "DIFFERENT!\n";
    }

    return 0;
}