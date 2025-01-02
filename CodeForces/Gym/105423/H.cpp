#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 Inf = 1e15, Mod = 998244353;
constexpr int N = 1e4, K = 10, L = 100;

std::vector<int> get(std::string s) {
    int l = s.length();
    std::vector nxt(l, 0);

    for (int i = 1; i < l; i++) {
        int j = nxt[i - 1];
        while (j && s[i] != s[j]) {
            j = nxt[j - 1];
        }
        nxt[i] = j + (s[i] == s[j]);
    }
    
    return nxt;
}

int main () {
    int n = 0, m = 0;
    std::string s{};
    std::cin >> n >> m >> s;
    int l = s.length();

    std::vector f(n, std::vector(m + 2, std::vector(l, 0ll)));
    f[0][0][0] = 25;
    f[0][l == 1 ? 1 : 0][1 % l] = 1;
    
    auto nxt = get(s);
    for (int i = 0; i + 1 < n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k < l; k++) {
                for (char c = 'a'; c <= 'z'; c++) 
                {
                    int cur = k;
                    while (cur && s[cur] != c) {
                        cur = nxt[cur - 1];
                    }
                    // 第一个字符就匹配失败
                    if (s[cur] == c) {
                        cur++;
                    }
                    (f[i + 1][j + (cur == l ? 1 : 0)][cur % l] += f[i][j][k]) %= Mod;
                }
            }
        }
    }
    
    i64 ans = 0;
    for (int i = 0; i < l; i++) {
        (ans += f[n - 1][m][i]) %= Mod;
    }
    std::cout << ans << '\n';
    system("pause");
    return 0;
}
