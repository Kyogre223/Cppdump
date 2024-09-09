//
// Created by Lin Kai on 9/9/24.
//

#include "Pool.h"



int main() {

    ThreadPool pool(4, 4);
    auto res1 = pool.enqueue(foo, 4, 2);
    pool.enqueue(bar);
    std::cout << res1.get() << '\n';




    return 0;
}