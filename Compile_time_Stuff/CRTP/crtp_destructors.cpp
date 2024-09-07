//
// Created by Lin Kai on 7/9/24.
//

#include "crtp_destructors.h"


int main() {
    Base<Derived>* obj = new Derived();
    obj->callDerivedMethod(); // Calls the derived method
    delete obj; // Safely deletes the derived object, invoking virtual destructor
    return 0;
}