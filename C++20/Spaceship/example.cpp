//
// Created by Lin Kai on 17/9/24.
//

#include "example.h"


int main() {
    A a{10, "Hello world!\n"};
    A b{20, "Hello world!\n"};
    std::priority_queue<A, std::vector<A>, std::less<A>>pq;
    if (a < b) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
    char c[5] = "Hell";
    foo(c);
    return 0;
}
