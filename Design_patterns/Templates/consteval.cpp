//
// Created by Lin Kai on 24/9/24.
//

#include <iostream>
#include <vector>
#include <string>

// consteval enforces compile time, and fails in compilation.
consteval size_t length(char const* s) {
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
    length(ptr);

    return 0;
}