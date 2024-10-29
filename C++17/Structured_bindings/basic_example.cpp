//
// Created by Lin Kai on 24/10/24.
//

#include <iostream>
#include <vector>
#include <memory>
#include <atomic>


template <typename T>
struct A{

};

struct MyStruct {
    std::string name_;
    int x_;
public:
    MyStruct() {
        std::cout << "Default\n";
    }

    MyStruct(std::string name, int x):name_{name}, x_{x}{
        std::cout << "Constructed\n";
    }

    MyStruct(MyStruct const& other) {
        std::cout << "copy ctor\n";
    }

    MyStruct(MyStruct&& other) {
        std::cout << "Move ctor\n";
    }

    MyStruct& operator = (MyStruct const& other) {
        std::cout << "Assignment copy\n";
        return *this;
    }

    MyStruct& operator = (MyStruct&& other) {
        std::cout << "Assignment move\n";
        return *this;
    }


};

MyStruct get() {
    return MyStruct{"Kai", 24};
}




int main() {

    static_assert(std::is_same_v<A<int>, A<int>>);
    static_assert(std::same_as<A<int>, A<int>>);

    auto [u, v] = get();
    // is the same as
    // auto e = get();
    // auto u = e.first;
    // auto v = e.second;

    return 0;
}
