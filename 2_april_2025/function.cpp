#include <iostream>
#include <cmath>
#include <algorithm>
#include <memory>
#include <bits/stdc++.h>

namespace func {

    template <typename T>
    class MyFunction;

    template <typename Ret, typename... Args>
    class MyFunction<Ret(Args...)> {
        public:

        MyFunction(Ret(*f)(Args...)):data_(std::make_unique<Child<decltype(f)>>(f)) {
        }

        Ret operator () (Args... args) {

            return data_->call(args...);
        }
        struct Base {
            Base() = default;
            virtual Ret call(Args... args) = 0;
            ~Base() = default;
        };

        template <typename T>
        struct Child: public Base {
            Child(T obj) {
                obj_ = obj;
            } 
            Ret call(Args... args) override {
                
                return obj_(args...);
            }
            ~Child() = default;
            T obj_;
        };
        private:
        std::unique_ptr<Base>data_;
    };
};


int add(int x, int y) {return x + y;}
void call(int x, int y) {std::cout << x + y << '\n';}

int main() {
    std::string s;
    std::cout << sizeof(s) << '\n';
    func::MyFunction<int(int, int)> obj = add;
    std::cout << obj(2, 3) << '\n';
    func::MyFunction<void(int, int)> obj2 = call;
    obj2(3, 6);
    return 0;
}
