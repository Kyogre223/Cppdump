//
// Created by Lin Kai on 10/9/24.
//

#ifndef CPPDUMP_BASIC_VISITOR_H
#define CPPDUMP_BASIC_VISITOR_H


#include <iostream>

class Cat;
class Dog;

class PetVisitor {
public:
    virtual void visit(Cat* c) = 0;
    virtual void visit(Dog* d) = 0;
};

class VisitingVisitor : public PetVisitor {
public:
    void visit(Cat* c) override {
        std::cout << "cat visitor \n";
    }

    void visit(Dog* d) override {
        std::cout << "Dog visitor \n";
    }
};



class Pet {
public:
    virtual ~Pet() {}
    Pet(std::string_view color): color_(color){}
    const std::string& color() const {return color_;}
    virtual void accept(PetVisitor& v) = 0;
    std::string color_;
};

class Cat: public Pet {
public:
    Cat(std::string_view color): Pet(color){}
    void accept(PetVisitor& v) override {
        v.visit(this);
    }
};

class Dog: public Pet {
public:
    Dog(std::string_view color): Pet(color){}
    void accept(PetVisitor& v) override {
        v.visit(this);
    }
};

#endif //CPPDUMP_BASIC_VISITOR_H
