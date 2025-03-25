#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define IOS
#else
    #define debug(...)
    #define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 1e5, M = 1e5, Inf = 1e9;

struct Hash
{
    const i64 P = 1e12 + 39;
    const int B = 13331;
    std::vector<i64> h, p;
    Hash(std::string s) : h(s.size() + 1), p(s.size() + 1) {
        int n = s.size();
        p[0] = 1;
        for (int i = 0; i < n; i++) {
            h[i + 1] = (h[i] * B + s[i]) % P;
            p[i + 1] = p[i] * B % P;
        }
    }

    //左闭右开 从 0 开始, 返回字串的哈希值
    i64 get(int l, int r) {
        return (h[r] + __int128(h[l]) * (P - p[r - l])) % P;
    }
};

void solve()
{
    std::string s;
    std::cin >> s;
    std::cout << s;
    int n = s.size();
    Hash h(s);
    std::reverse(s.begin(), s.end());
    Hash ih(s);

    for (int i = 0; i < n; i++) {
        // 检查 s[l r] 是否是回文
        int l = i, r = n - 1;
        int ml = l + r >> 1, mr = l + r + 1 >> 1;
        if (h.get(l, ml + 1) == ih.get(n - 1 - r, n - mr)) {
            std::cout << s.substr(n - i, i) << '\n';
            return;
        }
    }
}

int main()
{
    IOS;
    int _t = 1;
    // std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }

    system("pause");

    return 0;
}