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





void test() {
    ll a, b;
    constexpr ll MOD = 1e9 + 7;
    cin >> a >> b;
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    std::cout << res << '\n';
}

int main() {
    int n;
    cin >> n;
    while (n--) test();

    return 0;
}
