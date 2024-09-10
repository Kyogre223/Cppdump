//
// Created by Lin Kai on 10/9/24.
//

#include "No_except_decorator.h"


int main() {

    std::vector<Person>v = {"A", "B", "C"};
    std::cout << "Capacity: " << v.capacity() << '\n';
    v.push_back("D");
    std::cout << "NEW CAP " << v.capacity() << '\n';

    return 0;
}