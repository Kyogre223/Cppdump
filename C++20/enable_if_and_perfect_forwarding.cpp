//
// Created by Lin Kai on 23/10/24.
//

#include <iostream>
#include <compare>
#include <concepts>

// C++ 14's feature

template <typename T>
struct A {
    using type = int;

    type a = 4;

};
template <typename T>
using A_t = typename A<T>::type;

class Person {
private:
    std::string name_;

public:
    template <typename T, typename = std::enable_if<std::is_convertible<T, std::string>::value>::type>
    Person(T name):name_{name}{}
};

// why not perfect forward it instead ?
// copy constructor stops working!

int main() {
    std::string s = "kai";
    Person p1(s);
    Person p2("Lin");
    Person p3(p1);
    Person p4(std::move(p1));



    return 0;
}
