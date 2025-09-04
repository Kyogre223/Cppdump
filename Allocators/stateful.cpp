#include <iostream>
#include <vector>
#include <type_traits>
#include <array>
#include <memory>       // std::align


// stateless allocator
template <typename T>
struct stateless_alloc {
    using value_type = T;
    using size_type = std::size_t;
    using is_always_equal = std::true_type; // deprecated in C++23 
    
    stateless_alloc()=default;
    template <typename U>
    constexpr stateless_alloc(const stateless_alloc<U>&) noexcept {}


    T* allocate(size_type n) {
        return static_cast<T*>(::operator new(sizeof(T) * n));
    }

    void deallocate(T* p, size_type n) {
        ::operator delete(p, n * sizeof(T));
    }


};


struct MonotonicArena {
    std::byte* begin{};
    std::byte* end{};
    std::byte* cur{};
    MonotonicArena() = default;
    MonotonicArena(void* buffer, std::size_t bytes):
    begin{static_cast<std::byte*>(buffer)}, end{begin + bytes}, cur{begin} {

    }

    std::size_t remaining() const {
        return static_cast<std::size_t>(end - cur);
    }
};

template <typename T>
class stateful_allocator {
    public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    using is_always_equal = std::false_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_copy_assignment = std::true_type;
    using propagate_on_container_swap = std::true_type;

    private:
    template <class>
    friend class stateful_allocator;
    MonotonicArena* arena_ = nullptr;

    public:

    stateful_allocator() noexcept = default;
    explicit stateful_allocator(MonotonicArena* arena) noexcept :arena_(arena) {

    }

    template <typename U>
    stateful_allocator(const stateful_allocator<U>& other): arena_(other.arena_) {}

    T* allocate(size_type n) {
        if (!arena_) throw std::bad_alloc{};

        if (n > max_size()) throw std::bad_alloc{};
        std::size_t bytes = n * sizeof(T);
        void* p = arena_->cur;
        std::size_t space = arena_->remaining();

        if (!std::align(alignof(T), bytes, p, space)) {
            throw std::bad_alloc{};
        }

        auto* aligned = static_cast<std::byte*>(p);
    
        arena_->cur = aligned + bytes;

        return reinterpret_cast<T*>(aligned);


    }
    void deallocate(pointer, size_type) noexcept {
    }

    size_type max_size() const noexcept {
        if (!arena_) return 0;
        return arena_->remaining() / sizeof(T);
    }

    template <class U>
    friend bool operator==(const stateful_allocator& a, const stateful_allocator<U>& b) noexcept {
        return a.arena_ == b.arena_;
    }
    template <class U>
    friend bool operator!=(const stateful_allocator& a, const stateful_allocator<U>& b) noexcept {
        return !(a == b);
    }
};




int main() {

    std::vector<int, stateless_alloc<int>>vec;
    vec.reserve(10);
    vec.push_back(2);

    std::array<std::byte, 4096> storage{};
    MonotonicArena arena(storage.data(), storage.size());

    stateful_allocator<int> alloc(&arena);
    std::vector<int, stateful_allocator<int>> v(alloc);

    v.reserve(128);
    for (int i = 0; i < 100; ++i) v.push_back(i);



    return 0;
}
