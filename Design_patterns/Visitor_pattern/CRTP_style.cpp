//
// Created by Lin Kai on 7/10/24.
//


#include <iostream>
#include <assert.h>

// double dispatch?
// remove cyclic dependency (now we dont need to pair (p1, p2) tuple as a key)
// okay how about compile time efficiencies?
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
    virtual void feed(Visitor& v) = 0;
private:
    std::string color_;
};

template <typename T>
class Visitable: public Pet {
public:
    using Pet::Pet;
    void feed(Visitor& v) override {
        v.visit(static_cast<T*>(this));
    }
};

class Cat : public Visitable<Cat> {
    using Visitable<Cat>::Visitable;
};



int main() {
    Visitor f;
    Cat c("red");
    c.feed(f);
    return 0;
}