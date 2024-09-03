//
// Created by Lin Kai on 3/9/24.
//

#include "Inheritance_optimisations.h"


int main() {
    Derived d;
    Derived* ptr = &d;
    std::cout << "Derived: " << ptr << " Base1: " << static_cast<Base1*>(ptr) << " Base2: " << static_cast<Base2*>(ptr) << '\n';
    Derived2 d2;
    Derived2* ptr2 = &d2;
    std::cout << "Derived: " << ptr2 << " Base3: " << static_cast<Base3*>(ptr2) << " Base4: " << static_cast<Base4*>(ptr2) << '\n';

    return 0;
}
