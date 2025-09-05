#include <algorithm>
#include <cstdint>
#include <vector>
#include <cassert>
#include <list>

template <typename T>
class StatelessAllocator {
    public:
    using value_type = T;
    using size_type = std::size_t;
    using is_always_equal = std::true_type;
    
    using propagate_on_container_copy_assignment = std::false_type;
    using propagate_on_container_move_assignment = std::false_type;
    using propagate_on_container_swap = std::false_type;

    StatelessAllocator() = default;

    template <typename U>
    StatelessAllocator(const StatelessAllocator<U>& other) {}
    T* allocate(size_type n) {
        size_type required = n * sizeof(T);
        return static_cast<T*>(::operator new(required));
    }

    void deallocate(T* p, size_type n) {
        ::operator delete(p);
    }


};

template <typename T, typename U>
constexpr bool operator == (const StatelessAllocator<T>& t, const StatelessAllocator<U>& u) {
    return true;
}

template <typename T, typename U>
constexpr bool operator != (const StatelessAllocator<T>& t, const StatelessAllocator<U>& u) {
    return false;
}


// TASK B

// TASK B (corrected)

class NodePool {
private:
    using Data = void*;
    std::list<Data> resources_{};
    std::size_t size_{};

public:
    explicit NodePool(std::size_t size) : size_{size} {}

    Data get_resource() {
        if (resources_.empty()) {
            resources_.push_back(::operator new(size_)); // assumes align <= max_align_t
        }
        Data p = resources_.back();
        resources_.pop_back();
        return p;
    }

    void release(void* data) {
        resources_.push_back(data);
    }

    ~NodePool() {
        while (!resources_.empty()) {
            ::operator delete(resources_.back());
            resources_.pop_back();
        }
    }
};

template <typename T>
class NodePoolAllocator {
public:
    template <typename> friend class NodePoolAllocator;
    NodePool* resource_ = nullptr;

public:
    using value_type = T;
    using size_type = std::size_t;

    using is_always_equal = std::false_type;
    using propagate_on_container_copy_assignment = std::true_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap = std::true_type;

    NodePoolAllocator() = default;
    explicit NodePoolAllocator(NodePool* res) : resource_{res} {}

    template <typename U>
    NodePoolAllocator(const NodePoolAllocator<U>& other) : resource_{other.resource_} {}

    T* allocate(size_type n) {
        if (!resource_) throw std::bad_alloc();
        if (n != 1) throw std::bad_alloc(); // node containers expect n == 1
        return static_cast<T*>(resource_->get_resource());
    }

    void deallocate(T* p, size_type /*n*/) noexcept {
        if (!p) return;
        // ignoring n because we enforce n==1 on allocate
        resource_->release(static_cast<void*>(p));
    }
};

// Allocators compare equal iff they manage the same pool (resource identity).
template <typename T, typename U>
constexpr bool operator==(const NodePoolAllocator<T>& a, const NodePoolAllocator<U>& b) noexcept {
    return a.resource_ == b.resource_;
}
template <typename T, typename U>
constexpr bool operator!=(const NodePoolAllocator<T>& a, const NodePoolAllocator<U>& b) noexcept {
    return !(a == b);
}









static void test_stateless_vector() {
    using namespace std;
    using A = StatelessAllocator<int>;
    static_assert(A::is_always_equal::value);
    vector<int, A> x, y;
    for (int i=0;i<1000;++i) y.push_back(i);
    x = std::move(y); // should steal storage (IAE=true even though POCMA=false)
    assert(x.size()==1000);
}

static void test_node_pool_list() {
    using namespace std;
    NodePool p1(sizeof(list<int>::value_type));
    NodePool p2(sizeof(list<int>::value_type));
    using A = NodePoolAllocator<int>;
    list<int, A> a{A(&p1)}, b{A(&p2)};
    for (int i=0;i<1000;++i) b.push_back(i);
    a = b; // POCCA=true -> a adopts p2
    // both now use p2
    b.push_back(42);
    a.push_back(43);
    assert(!a.empty() && !b.empty());
    // move assignment should be cheap due to POCMA=true
    list<int, A> c{A(&p1)};
    c = std::move(a);
    assert(!c.empty());
}



int main() {
    test_stateless_vector();
    test_node_pool_list();



    return 0;
}
