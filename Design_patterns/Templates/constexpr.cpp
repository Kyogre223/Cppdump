//
// Created by Lin Kai on 24/9/24.
//

#include <iostream>
#include <vector>
#include <string>

constexpr size_t length(char const* s) {
    size_t res = 0;
    while (*s) {
        ++res;
        ++s;
    }
    return res;
}


int main() {
    static_assert(length("abc") == 3);

    char const* ptr = "Hello\n";
    static_assert(length(ptr) == 6);

    return 0;
}