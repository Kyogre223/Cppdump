//
// Created by Lin Kai on 25/8/24.
//

#include "std_any.h"

using ll = long long;
int main() {
    std::queue<int>q1, q2;
    for (int i = 0; i < 5; ++i) q1.push(i);
    for (int i = 2; i < 8; ++i) q2.push(i);
    q1.swap(q2);
    while (!q1.empty()) {
        std::cout << q1.front() << '\n'; q1.pop();
    }
    MyAny a2 = 20;
    std::cout << MyAnyCast<int>(a2) << '\n';

    return 0;
}
