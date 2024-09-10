//
// Created by Lin Kai on 10/9/24.
//

#ifndef CPPDUMP_NO_EXCEPT_DECORATOR_H
#define CPPDUMP_NO_EXCEPT_DECORATOR_H


#include <iostream>
#include <vector>
#include <string>

struct Person {
    std::string name;
    Person(char const* n): name(n){
        std::cout << "INIT\n";
    }
    Person(Person const& P):name(P.name){
        std::cout << "CPY\n";
    }
    Person(Person const&& P) noexcept : name(std::move(P.name)){
            std::cout << "MOVE\n";
    }

};

#endif //CPPDUMP_NO_EXCEPT_DECORATOR_H
