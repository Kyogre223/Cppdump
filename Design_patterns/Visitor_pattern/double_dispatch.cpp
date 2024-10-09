//
// Created by Lin Kai on 7/10/24.
//

#include <iostream>




// double dispatch?
class Cat;
class Dog;

class Visitor {
public:
    virtual void visit(Cat* c) = 0;
    virtual void visit(Dog* d) = 0;
};

class FeedV : public Visitor {
public:
    void visit(Cat* c) override {
        std::cout << "Feeding tuna\n";
    }
    void visit(Dog* d) override {
        std::cout << "Feeding steak\n";
    }
};

class Pet {
public:
    Pet(std::string_view color): color_{color} {}
    virtual void feed(Visitor& v) = 0;
private:
    std::string color_;
};

class Cat: public Pet {
public:
    Cat(std::string_view color): Pet{color} {}

    void feed(Visitor& v) override {
        v.visit(this);
        std::cout << "I am feeding a cat\n";
    }
};

class Dog: public Pet {
public:
    Dog(std::string_view color): Pet{color}{}

    void feed(Visitor& v) override {
        v.visit(this);
        std::cout << "I am feeding a dog\n";
    }
};



int main() {
    FeedV f;
    Dog d("red");
    d.feed(f);
    return 0;
}
