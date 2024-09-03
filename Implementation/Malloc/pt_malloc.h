//
// Created by Lin Kai on 3/9/24.
//

#ifndef CPPDUMP_PT_MALLOC_H
#define CPPDUMP_PT_MALLOC_H

#include <iostream>
#include <cstring>
#include <string>
#include <functional>
#include <memory>
#include <variant>
#include <unistd.h>
#include <sys/mman.h>

using word_t = int64_t; // imagine we are on a 64 bit architecture

constexpr int THRESHOLD = 1300; // threshold to use mmap

// simple allocator, not going to use the forward and backwards pointers in explicit free lists.
struct Block {
    // ========= 0 byte =======
    int arena = 0; // header  4 bytes
    int size = 0; // header  4 bytes
    bool used = false; // header  1 byte
    bool isMMap = false; // header 1 byte
    // ========== 10 bytes ========

    // starts at 16 byte =======
    Block* next = nullptr; // I am going to leave out the pred pointer, for simplicity.


    word_t data[1]; // our payload;
};
// in total, each block is at least, 32 bytes.

int align(int size) {
    return (size + sizeof(word_t) - 1) & ~(sizeof(word_t) - 1);
}

Block* getHeader(void* p) {
    return (Block*)((char*)p + sizeof(Block::data) - sizeof(Block));
}

struct MyHeap {
    inline static Block* originalTop = nullptr;
    inline static Block* currentTop = nullptr;
    word_t* allocate(int size) {
        std::cout << "Allocated size: " << size << '\n';
        size = align(size);
        std::cout << "Aligned size: " << size << '\n';
        int requiredSize = size + sizeof(Block) - sizeof(Block::data);
        std::cout << "Required size is actually: " << requiredSize << '\n';


        // use sbrk if the required chunk size is smaller than threshold
        if (requiredSize <= THRESHOLD) {
            Block* ptr = static_cast<Block*>(sbrk(0));
            if (sbrk(requiredSize) == (void*)(-1)) {
                return nullptr; // we are OOM!;
            }
            if (originalTop == nullptr) originalTop = ptr;
            if (currentTop == nullptr) {
                currentTop = ptr;
            } else {
                currentTop->next = ptr;
            }
            ptr->arena = 0;
            ptr->size = requiredSize;
            ptr->used = true;
            return ptr->data;
        }

        Block* ptr = static_cast<Block*>(mmap(0, requiredSize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0));
        if (ptr == MAP_FAILED) {
            return nullptr; // mmap failed
        }
        ptr->arena = 0;
        ptr->size = requiredSize;
        ptr->used = true;
        ptr->isMMap = true;
        std::cout << "MMAP is used\n";
        return ptr->data;

    }

    void deallocate(void* p) {
        std::cout << "Deallocate called!\n";
        if (!p) return;
        // our void ptr returns the payload data. we need to get the header

        if (getHeader(p)->isMMap) {
            munmap(p, getHeader(p)->size);
        } else {
            // can extend to coalescing....
            getHeader(p)->size = 0;
            getHeader(p)->used = false;
        }

    }

    ~MyHeap() {
        // could extend on coalescing
        auto ptr = originalTop;
        int tot = 0;
        while (ptr != nullptr) {
            tot += ptr->size;
            ptr = ptr->next;
        }
        // Move the program break back to the original
        if (sbrk(-tot) == (void*)(-1)) {
            std::cerr << "Failed to reset the program break\n";
        } else {
            std::cout << "Successfully reset the program break\n";
        }
    }
};

void* operator new (size_t size, MyHeap* ptr) {

    return ptr->allocate(size);
}


void operator delete(void* ptr, MyHeap* heap) {
    std::cout << "overloaded delete operator called!\n";
    heap->deallocate(ptr);
}

struct A {
    int a = 0;
    int b = 1;
    int c = 2;
};

using ll = long long;


#endif //CPPDUMP_PT_MALLOC_H
