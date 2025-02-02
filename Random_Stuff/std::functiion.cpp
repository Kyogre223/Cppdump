#include <bits/stdc++.h>
#include <string>
#include <string_view>
#include <cstddef>      // for std::size_t
#include <type_traits>  // for std::integral_constant
#include <utility>      // for std::forward
#include <memory>


template <typename T>
class MyFunction{};

template <typename Ret, typename... Args>
class MyFunction<Ret(Args...)> {
    // implements a type erased operator ()
    public:
    
    MyFunction(Ret(*ptr)(Args...)):data_(std::make_unique<Child<decltype(ptr)>>(ptr)){
        
    }

    Ret operator () (Args... args) {

        return data_->call(args...);
    }
    class Base {
        public:
        Base() = default;
        virtual ~Base() = default;
        virtual Ret call(Args...) = 0;
    };

    template <typename T>
    class Child : public Base {
        public:
        Child(T ctor):obj_(ctor){

        }
        Ret call(Args... args) {
            return obj_(args...);
        }
        T obj_;
    };

    private:
    std::unique_ptr<Base>data_;
};

void foo(int i, int j) {
    std::cout << "Hello " << i << ' ' << j << '\n';
}

int main() {

    MyFunction<void(int, int)>Kai = foo;
    Kai(2, 5);

    return 0;
}
