//
// Created by Lin Kai on 7/9/24.
//

#include "basic_crtp.h"


int main() {
    A<B>* ptr = new B();
    ptr->call();

    delete ptr;
    return 0;
}
