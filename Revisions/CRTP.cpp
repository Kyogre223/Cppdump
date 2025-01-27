#include <bits/stdc++.h>
#include <string>
#include <string_view>
#include <cstddef>      // for std::size_t
#include <type_traits>  // for std::integral_constant
#include <utility>      // for std::forward


template <typename T>
class Base {
    public:

    decltype(auto) convert() const {
        return static_cast<T const&>(*this);
    }

    decltype(auto) convert() {
        return static_cast<T&>(*this);
    }
    
    void call() const {
        convert().shout();
    }

    void pee() const {
        convert().pee();
    }

    protected:
    ~Base() = default;
};


class Bird : public Base<Bird> {
    public:
    void shout() const {
        std::cout << "Bird is calling!\n";
    }
    void pee() const {
        std::cout << "Bird is peeing\n";
    }
};

class Tiger: public Base<Tiger> {
    public:
    void shout() const {
        std::cout << "Tiger is calling!\n";
    }
    void pee() const {
        std::cout << "Tiger is peeing\n";
    }

};



int main() {
    Tiger tig;
    tig.call();
    return 0;
}
