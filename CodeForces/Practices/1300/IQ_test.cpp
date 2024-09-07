//
// Created by Lin Kai on 7/9/24.
//
#include <bits/stdc++.h>


using namespace std;
int main() {
    int n;
    cin >> n;
    vector<int>A(n, 0);
    for (int i = 0; i < n; ++i) cin >> A[i];
    int o = 0, e = 0;
    int f = -1, s = -1;
    for (int i = 0; i < n; ++i) {
        int x = A[i];
        if (x % 2 == 0) {
            ++e;
            s = i;
        } else {
            ++o;
            f = i;
        }
    }
    if (o == 1) {
        std::cout << ++f << '\n';
    } else {
        std::cout << ++s << '\n';
    }

    return 0;
}
