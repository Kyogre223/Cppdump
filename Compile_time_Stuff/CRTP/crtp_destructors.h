//
// Created by Lin Kai on 7/9/24.
//

#ifndef CPPDUMP_CRTP_DESTRUCTORS_H
#define CPPDUMP_CRTP_DESTRUCTORS_H

#include <iostream>

// CRTP Base class with a virtual destructor
template <typename Derived>
class Base {
public:
    // Virtual destructor for polymorphic deletion
    virtual ~Base() {
        std::cout << "Base destructor\n";
    }

    // Method that calls a method from the derived class using CRTP
    void callDerivedMethod() {
        static_cast<Derived*>(this)->derivedMethod();
    }
};

// Derived class inheriting from the CRTP base
class Derived : public Base<Derived> {
public:
    ~Derived() {
        std::cout << "Derived destructor\n";
    }

    void derivedMethod() {
        std::cout << "Derived method called!\n";
    }
};


#endif //CPPDUMP_CRTP_DESTRUCTORS_H
