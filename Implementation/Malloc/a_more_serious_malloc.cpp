#include <utility>
#include <iostream>
#include <vector>
#include <memory>
#include <unistd.h>
#include <assert.h>
using word_t = size_t;

#define INIT_SIZE 1050
#define MMAP_THRESHOLD 130000 // 130KB

inline size_t align(size_t n) {
    return (n + sizeof(word_t) * 2 - 1) & ~(sizeof(word_t) * 2 - 1);
}

inline bool is_main_arena(size_t n) {
    return !((n) & (1 << 2));
}

inline bool is_mmap(size_t n) {
    return n & 2;
}

inline bool is_free(size_t n) {
    return n & 1;
}




struct chunk {
    size_t prev_;
    size_t cur_; // current size A , M , F (use F instead of P)
    // A = main arena or not
    // M = mmaped or not
    // P = prev size is free or not.
    // F = current block is free or not
    // here actually,
    chunk* fd_ptr_;
    chunk* bk_ptr_;

    // omit the big chunk pointers here for simplciity.
};

int ASKED = 0;
struct Heap {
    chunk* currentTop = nullptr; // will never belong in any bins
    chunk* freeList = nullptr; // our free list.
    chunk* initialStart = nullptr;
    Heap() {
        // ===== init logic here
        auto top = sbrk(0);
        size_t init = align(INIT_SIZE);
        std::cout << "INIT size " << init << '\n';
        ASKED += init;
        if (sbrk((init)) == (void*)(-1)) {
            std::terminate(); // WE CANNOT EVEN INIT;
        }
        initialStart = static_cast<chunk*>(top);
        initialStart->cur_ = 0;
        currentTop = (chunk*)((char*)initialStart + 32); // header , prev, bk, fd pointers.
        initialStart->fd_ptr_ = currentTop;
        currentTop -> cur_ = init - 16 - 32; // for the metadata
        std::cout << "CURRENTTOP " << currentTop->cur_ << '\n';
    }
    void* get_chunk(size_t n) {
        std::cout << "initial n " << n << '\n';
        // N IS ALREADY INCLUSIVE OF THE HEADER.

        // ============== first check through the free list ===========
        if (freeList) {
            auto it = freeList;
            // first fit
            void* res = nullptr;
            while (it ->cur_ < n) {
                it = it->fd_ptr_;
            };
            if (it != nullptr) {
                std::cout << "Used\n";
                // here we can split it again also,
                // invalidate the pointers
                return (void*)it->fd_ptr_;

            }
        }
        // ============== if free list has non available, request from the current Top ======
        std::cout << "Total size " << n + 16 << '\n';
        if (currentTop->cur_ - n >= 16 ) {
            size_t remaining = currentTop->cur_ - n - 16;
            currentTop ->cur_ = n;
            chunk* nxt = (chunk*)((char*)currentTop + n + 16);
            nxt->cur_ = remaining;
            auto tmp = currentTop;
            nxt ->prev_ = n - 16;
            void* res = (char*)currentTop + 16;
            std::swap(nxt, currentTop);
            return res;
        } else {
            // use MMAP or more sbrk ()
        }
    }

    void* allocate(size_t n) {
        n = align(n); // aligned the user allocated region properly.

        return get_chunk(n);
    }
    chunk* get_previous_chunk_ptr(void* ptr) {
        // check my current previous size
        chunk* cptr = (chunk*)((char*)ptr - 16);
        size_t prevSize = cptr->prev_;

        return (chunk*)((char*)cptr - prevSize - 16);
    }

    chunk* get_next_chunk_ptr(void* ptr) {
        chunk* cptr = (chunk*)((char*)ptr - 16);
        size_t curSize = cptr->cur_;

        chunk* ret = (chunk*)((char*)ptr + curSize + 16);
        return ret;
    }

    void free(void* ptr) {
        // add it inside our free list, coalesce
        chunk* cptr = (chunk*)((char*)ptr - 16);
        if (freeList == nullptr) {

            freeList = cptr;
            freeList->fd_ptr_ = nullptr;
        } else {

            cptr->fd_ptr_ = freeList;
            freeList->bk_ptr_ = cptr;
            freeList = cptr;
        }
    }

    ~Heap() {
        // add all of our data together, and then -sbrk together.
        chunk* it = freeList;
        size_t total = 0;
        int remain = 0;

        // Deallocate everything in the free list
        while (it != nullptr) {
            total += it->cur_;
            total += 16;
            remain += it->cur_ + 16;
            std::cout << "Deallocated free chunk from free list: " << total << '\n';
            it = it->fd_ptr_;
        }
        total += 32 + 16 + currentTop->cur_;
        sbrk(-total);
        std::cout << "Additionally " << total  << '\n';



    }

};


int main() {
    static_assert(sizeof(size_t) == 8); // 64 bit machine
    Heap h;
    void* f = h.allocate(130);
    void* f2 = h.allocate(220);
    void* f3 = h.allocate(300);

    h.free(f);
    h.free(f2);
    h.free(f3);
    std::cout << "TOtal memory asked " << ASKED << '\n';
    return 0;
}
