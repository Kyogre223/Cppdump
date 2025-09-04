#include <iostream>
#include <vector>
#include <type_traits>


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


int main() {

    std::vector<int, stateless_alloc<int>>vec;
    vec.reserve(10);
    vec.push_back(2);



    return 0;
}
