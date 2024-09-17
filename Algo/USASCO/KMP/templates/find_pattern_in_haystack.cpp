//
// Created by Lin Kai on 15/9/24.
//


class Solution {
public:
    vector<int> prefix_function(string s) {
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
    int strStr(string haystack, string needle) {
        vector<int>table = prefix_function(needle);
        int i = 0, j = 0;
        while (i < haystack.size() && j < needle.size()) {
            if (haystack[i] == needle[j]) {
                ++i;
                ++j;
            }
            if (j == needle.size()) return i - j;
            if (i < haystack.size() && needle[j] != haystack[i]) {
                if (j > 0) {
                    j = table[j - 1];
                } else {
                    ++i;
                }
            }
        }
        return -1;
    }
};