//
// Created by Lin Kai on 7/10/24.
//


#include <iostream>
#include <assert.h>

// double dispatch?
// remove cyclic dependency (now we dont need to pair (p1, p2) tuple as a key)
// okay how about compile time efficiencies? -> use the base class as a static function container



class Cat;
class Dog;

class Visitor {
public:
    void visit(Cat* c) {
        std::cout << "Visiting\n";
    }
    virtual ~Visitor(){}
};


class Pet {
public:
    Pet(std::string_view color): color_{color} {}
    template <typename T1, typename T2>
    static void visit(T1& visitor, T2& visitable) {
        visitor.visit(&visitable);
    }
private:
    std::string color_;
};

class Cat {
public:
    Cat(std::string_view color):color_{color}{}

private:
    std::string color_;
};



int main() {
    Visitor f;
    Cat c("red");
    Pet::visit(f, c);
    return 0;
}