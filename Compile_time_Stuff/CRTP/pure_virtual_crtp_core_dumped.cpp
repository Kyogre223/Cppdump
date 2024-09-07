//
// Created by Lin Kai on 7/9/24.
//

#include "pure_virtual_crtp_core_dumped.h"



int main() {
    A<B>* ptr = new B();
    ptr->call();

    delete ptr;
    return 0;
}