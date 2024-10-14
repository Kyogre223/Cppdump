//
// Created by Lin Kai on 14/10/24.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <bits/stdc++.h>

template <typename T>
class Function;

template <typename Ret, typename... Args>
class Function<Ret(Args...)> {
public:
    Function(Ret (*f)(Args...)): ptr_{std::make_unique<Child<decltype(f)>>(f)}{}

    Ret operator () (Args... args) {
        return ptr_->call(args...);
    }

    struct Base {
        virtual Ret call(Args... args) = 0;
    };

    template <typename T>
    struct Child : public Base {
        Child(T callable): callable_(callable) {}
        Ret call(Args... args) override {
            return callable_(args...);
        }

        T callable_;
    };

private:

    std::unique_ptr<Base>ptr_;
};

int foo(int a, int b) {
    return a +b;
}

int main() {
    Function<int(int, int)> f = foo;
    std::cout << f(20, 30) << '\n';




    return 0;
}
