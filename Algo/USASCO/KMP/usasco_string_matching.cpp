#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> prefix_function(const string& s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

int main() {
    string s, p;
    cin >> s >> p;

    // Concatenate pattern, separator, and text
    string A = p + "#" + s;
    vector<int> table = prefix_function(A);

    int pattern_length = p.size();
    int count = 0;

    // Count occurrences of the pattern by checking prefix function values
    for (int i = pattern_length + 1; i < A.size(); i++) {
        if (table[i] == pattern_length) {
            count++;
        }
    }

    cout << count << '\n';
    return 0;
}