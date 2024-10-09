//
// Created by Lin Kai on 7/10/24.
//

#include <iostream>


class Pet {
public:
    Pet(std::string_view color): color_{color} {}
    virtual void feed() = 0;
private:
    std::string color_;
};

class Cat: public Pet {
public:
    Cat(std::string_view color): Pet{color} {}

    void feed() override {
        std::cout << "I am feeding a cat\n";
    }
};

class Dog: public Pet {
public:
    Dog(std::string_view color): Pet{color}{}

    void feed() override {
        std::cout << "I am feeding a dog\n";
    }
};



int main( ) {



    return 0;
}