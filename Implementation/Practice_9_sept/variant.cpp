//
// Created by Lin Kai on 9/9/24.
//

#include "variant.h"


int main() {

    myVariant<int, std::string, short>var(std::string("Hello world!\n"));
    std::cout << var.get<1>() << '\n';

    return 0;
}