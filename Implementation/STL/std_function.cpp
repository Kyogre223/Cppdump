//
// Created by Lin Kai on 2/9/24.
//

#include "std_function.h"


int main() {

    std::function<int(int, int)>f = add;
    std::cout << f(2, 3) << '\n';
    f = [](int a, int b)-> int {
        return a + b;
    };
    std::cout << f(3, 4) << '\n';
    // lets do a my std::function

    myF<int(int, int)>myF = add;
    std::cout << myF(2, 3) << '\n';
    myF = [](int a, int b)->int {
        return a + b;
    };
    std::cout << f(3, 4) << '\n';


    return 0;
}