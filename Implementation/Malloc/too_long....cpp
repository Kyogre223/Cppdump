//
// Created by Lin Kai on 21/9/24.
//\\\
#include <iostream>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <functional>
#include <thread>
#include <iostream>
#include <memory>
#include <algorithm>
#include <unistd.h>
#include <sys/mman.h>
#include <exception>


#define MMAP_THRESHOLD 130000 // 130 KB mmap threshold
#define INIT_SIZE 4096

using word_t = int64_t;
// memory optimisations

// first try to overload unique and shared ptr
// random malloc.

// first we carve out a big chunk from mmeory
class Malloc {
    struct Chunk {
        size_t prev_; // 8
        size_t size_; // 16
        bool isUsed = false; //17
        bool isMMaped = false; // 18
        Chunk* fd_; // forward ptr, 24
        Chunk* bk_; // backward ptr, 32
        word_t data[0]; // my payload;
    };
    Chunk* current_top_ = nullptr; // first big chunk of mem
    Chunk* free_list_ = nullptr; // current free list
    // if both dont have, repopulate current_top_ and try again.
public:
    Malloc() {
        current_top_ = static_cast<Chunk*>(sbrk(0));
        if (sbrk(INIT_SIZE) == (void*)(-1)) {
            throw std::runtime_error("Cannot init top chunk in malloc!");
        }
        current_top_->prev_ = 0;
        current_top_->size_ = INIT_SIZE - header_size();
        current_top_->isUsed = false;
        current_top_->isMMaped = false;
        current_top_->fd_ = current_top_->bk_ = nullptr;
    }
    size_t header_size() const {
        return 32;
    }
    size_t align(size_t size) {

        return (size + 8 - 1) & ~(8 - 1);
    }

    void* get_from_free_list(size_t size) {
        return nullptr;
    }
    void* allocate(size_t size) {
        std::cout << "original size " << size << '\n';
        size = align(size);
        size += header_size();
        std::cout << "after alignment size " << size << '\n';
        if (size >= MMAP_THRESHOLD) {
            Chunk* res = static_cast<Chunk*>(mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0));
            res ->isUsed = true;
            res->isMMaped = true;
            res->size_ = size - header_size();
            // dont need to coalesce this one since we are returning it.
            // hence, dont need to set prev_
            return (void*)(((char*)res + header_size()));
        }
        // if we reached here, that means we need to first find a block from the free list.
        void* res = get_from_free_list(size);
        if (res != nullptr) return res;
        // then carve out from a big chunk
        // what if the current top dont have enough? extend it.
        //... plan here properly!
        if ()



    }

    void* deallocate(void* ptr) {
        Chunk* ptr_ = reinterpret_cast<Chunk*>((char*) ptr - header_size());
        if (ptr_->isMMaped) {
            munmap((void*)ptr_, ptr_->size_ + header_size());
        }
        // coalesce or not?
        //

    }

};





class Heap {
public:
    void* allocate(size_t size) {
        // void* ptr = sbrk(0);
        // if (sbrk(size) == (void*)(-1)) {
        //     throw std::bad_alloc();
        // }
        // return ptr;
        void* ptr = std::malloc(size);
        return ptr;
    }
    void deallocate(void* ptr) {
        free(ptr);
    }
};

class Delete {
    Heap* heap;
public:
    Delete(Heap* ptr):heap{ptr}{}
    void operator () (void* ptr) {
        heap->deallocate(ptr);
    }
};


void* operator new (size_t size, Heap* ptr) {
    return ptr->allocate(size);
}




int main() {
    Heap heap;
    Delete del(&heap);
    std::unique_ptr<int, Delete>ptr(new (&heap) int(2), del);

    return 0;
}
