//
// Created by Lin Kai on 3/9/24.
//

#include "pt_malloc.h"



int main() {
    MyHeap heap;
    A* ptr = new (&heap) A{};
    if (getHeader(ptr)->data == (word_t*)ptr) {
        std::cout << "Get header is correct\n";
    }
    // but right now our heap, does nothing but keep bumping up the mmap
    operator delete (ptr, &heap);

    auto ptr2 = heap.allocate(1300); // resort to mmap
    heap.deallocate(ptr2);

    return 0;
}