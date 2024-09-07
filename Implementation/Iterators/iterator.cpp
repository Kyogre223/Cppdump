//
// Created by Lin Kai on 7/9/24.
//

#include "iterator.h"


int main() {
    myVector<int> vec(5);

    int i = 0;
    // for (auto it = vec.begin(); it != vec.end(); ++it) {
    //     *it = ++i;
    // }
    std::iota(vec.begin(), vec.end(), 1);

    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }

    return 0;
};