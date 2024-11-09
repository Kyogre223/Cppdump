//
// Created by Lin Kai on 9/11/24.
//

#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <cstring>
#include <set>
#include <algorithm>
#include <numeric>
#include <cstdlib>
using namespace std;
using ll = long long;


long long numberOfDivisors(long long num) {
    long long total = 1;
    for (int i = 2; (long long)i * i <= num; i++) {
        if (num % i == 0) {
            int e = 0;
            do {
                e++;
                num /= i;
            } while (num % i == 0);
            total *= e + 1;
        }
    }
    if (num > 1) {
        total *= 2;
    }
    return total;
}


void test() {
    ll N;
    cin >> N;
    std::cout << numberOfDivisors(N) << ' ';
}

int main() {
    int n;
    cin >> n;
    while (n--) test();

    return 0;
}
