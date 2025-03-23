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

    int l = 0, r = s.size() - 1;
    while (l < r && s[l] == s[r]) {
        l++, r--;
    }

    if (l >= r) {
        std::cout << 1 << ' ' << 1 << '\n';
        return;
    }
    Hash h(s);
    std::reverse(s.begin(), s.end());
    Hash ih(s);

    auto judge = [&](int l, int r) -> bool {
        if (l > r) {
            return true;
        }
        int ml = l + r >> 1;
        int mr = l + r + 1 >> 1;
        return h.get(l, ml + 1) == ih.get(s.size() - 1 - r, s.size() - 1 - mr + 1);
    };

    int L = -2, R = -2;
    for (int i = 1; i + i <= r - l + 1; i++) {
        if (h.get(l, l + i) == h.get(l + i, l + 2 * i) && judge(l + 2 * i, r)) {
            L = l + i, R = r;
            break;
        }
        if (h.get(l, l + i) == h.get(r + 1 - i, r + 1) && judge(l + i, r - i)) {
            L = l, R = l + i - 1;
            break;
        }
        if (h.get(r + 1 - i, r + 1) == h.get(r + 1 - 2 * i, r + 1 - i) && judge(l, r - 2 * i)) {
            L = l, R = r - i;
            break;
        }
    }
    std::cout << L + 1 << ' ' << R + 1 << '\n';
    return;
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