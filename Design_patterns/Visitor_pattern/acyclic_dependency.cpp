//
// Created by Lin Kai on 7/10/24.
//


#include <iostream>
#include <assert.h>

// double dispatch?
// remove cyclic dependency (now we dont need to pair (p1, p2) tuple as a key)
class Cat;
class Dog;


class Visitor {
public:

    virtual ~Visitor(){}
};

class CatVisitor {
public:
    virtual void visit(Cat* c) = 0;
};

class FeedingVisitor : public Visitor,
                       public CatVisitor {
public:
    void visit(Cat* c) override
    {
        std::cout << "Feeding tuna to the cat\n";
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
        if (CatVisitor* ptr = dynamic_cast<CatVisitor*>(&v)) {
            ptr->visit(this);
        } else {
            assert(false);
        }
        std::cout << "I am feeding a cat\n";
    }
};

class Dog: public Pet {
public:
    Dog(std::string_view color): Pet{color}{}

    void feed(Visitor& v) override {
        std::cout << "I am feeding a dog\n";
    }
};



int main() {
    FeedingVisitor f;
    Cat c("red");
    c.feed(f);
    return 0;
}
