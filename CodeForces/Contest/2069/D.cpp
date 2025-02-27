#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
#else
    #define debug(...)
    #define sp()
    #define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 1e5, M = 1e5, Inf = 1e9;

int solve()
{
    std::string s;
    std::cin >> s;
    int n = s.length();
    int l = 0;
    while (l + l < n && s[l] == s[n - l - 1]) {
        l++;
    }

    if (l + l == n) {
        return 0;
    }

    n -= 2 * l;
    auto t = "#" + s.substr(l, n);
    std::vector pre(n + 1, std::vector(26, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 26; j++) {
            pre[i][j] = pre[i - 1][j];
        }
        pre[i][t[i] - 'a']++;
    }

    bool ok = true;
    for (int i = 0; i < 26; i++) {
        if (pre[n / 2][i] * 2 != pre[n][i]) {
            ok = false;
            break;
        }
    }

    if (ok) {
        int p = n / 2;
        while (t[p] == t[n - p + 1]) {
            p--;
        }
        return p;
    }
    else {
        int p1 = 0, p2 = 0;
        std::vector cnt(26, 0);
        for (int i = 1; i <= n; i++) {
            int num = ++cnt[t[i] - 'a'];
            int sum = pre[n][t[i] - 'a'];
            
            if (i + i <= n) {
                if (num * 2 > sum && p1 == 0) {
                    p1 = i - 1;
                }
            }
            else if (num * 2 <= sum) {
                p2 = n - i;
            }
        }
        return n - std::max(p1, p2);
    }
}

int main()
{
    IOS;
    int _t = 1;
    std::cin >> _t;
    
    while (_t--)
    {
        std::cout << solve() << '\n';
    }

    sp();

    return 0;
}

/*
"#kktttteeekffkekkttfttf"
*/