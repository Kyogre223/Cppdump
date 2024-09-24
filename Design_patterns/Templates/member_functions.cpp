//
// Created by Lin Kai on 24/9/24.
//

#include <iostream>
#include <vector>
#include <string>

template <typename T>
struct ArrayOf2 {
    ArrayOf2(T a, T b) {
        arr[0] = a;
        arr[1] = b;
    }
    T sum() const {
        return arr[0] + arr[1]; // C still compiles, even though theres
    }

private:
    T arr[2];
};


int main() {
    ArrayOf2<int>A = {1, 2};
    ArrayOf2<double>B = {1, 2};
    char const* c = "Hello\n";
    ArrayOf2<char const*>C = {&c[0], &c[1]};



    return 0;
}
