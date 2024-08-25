//
// Created by Lin Kai on 25/8/24.
//

#include "thread_pool.h"


int main() {
    std::cout << "My thread pool!\n";

    ThreadPool pool(10, 10);
    auto f = pool.enqueue(add, 10, 3);
    auto f2 = pool.enqueue(minus, 10, 3);
    std::cout << f.get() << '\n';
    std::cout << f2.get() << '\n';


    return 0;
}