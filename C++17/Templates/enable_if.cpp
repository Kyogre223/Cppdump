//
// Created by Lin Kai on 29/10/24.
//

#include <iostream>
#include <type_traits>
#include <vector>


struct MyClass {
    std::string name_;

    MyClass() {
        std::cout << "Default ctor\n";
    }
    // MyClass(std::string& name):name_{(name)}{}

    // MyClass(std::string&& name):name_{std::move(name)}{}

    template<typename T, typename = std::enable_if_t<std::is_convertible_v<T, std::string>>>
    MyClass(T&& other):name_(std::forward<decltype(other)>(other)){}


    MyClass(MyClass const& cpy) {
        name_ = cpy.name_;
    }

    MyClass(MyClass&& other) {
        name_ = std::move(other.name_);
    }





};

void foo(MyClass) {
    std::cout << "Inside foo\n";
}

MyClass bar() {

    MyClass s;
    return s;
}



int main() {
    MyClass a;
    MyClass b(a);
    MyClass c("Kai");



    return 0;
}
