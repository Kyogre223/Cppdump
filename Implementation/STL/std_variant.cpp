//
// Created by Lin Kai on 25/8/24.
//

#include "std_variant.h"


int main() {
    std::cout << Impl::helper<int, long long, int, std::string>::value << '\n';
    K::MyVariant<int, long long, std::string> var(std::string("Hello world!\n"));
    std::cout << var.index() << '\n';
    std::cout << var.get<2>() << '\n';
    return 0;
}
