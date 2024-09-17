//
// Created by Lin Kai on 15/9/24.
//

vector<int> ans(n + 1);
for (int i = 0; i < n; i++)
ans[pi[i]]++;
for (int i = n-1; i > 0; i--)
ans[pi[i-1]] += ans[i];
for (int i = 0; i <= n; i++)
ans[i]++;


// where ans[i] is the occurrence of each prefix of length i

