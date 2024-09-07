#include <bits/stdc++.h>

int main() {
    int n;
    std::cin >> n;
    std::vector<std::string> A;
    std::string str;

    // Reading input strings
    for (int i = 0; i < n; ++i) {
        std::cin >> str;
        A.push_back(str);
    }
    std::unordered_map<std::string, int>mp;

    // Checking for duplicates and printing appropriate results
    for (int i = 0; i < n; ++i) {

        if (mp[A[i]] == 0) {
            std::cout << "OK\n";
            mp[A[i]]++;
        } else {
            std::cout << A[i] + std::to_string(mp[A[i]]++) << '\n';
        }
    }

    return 0;
}
