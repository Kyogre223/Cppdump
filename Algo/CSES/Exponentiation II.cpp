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
constexpr int MOD = 1e9 + 7;

ll binary(ll a, ll b, ll mod) {
    ll res = 1;

    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }

    return res;
}




void test() {
    ll a, b, c;
    cin >> a >> b >> c;
    ll res = binary(b, c, MOD - 1);
    std::cout << binary(a, res, MOD) << '\n';

}

int main() {
    int n;
    cin >> n;
    while (n--) test();

    return 0;
}
