#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 3e5, M = 1e5;

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

std::vector<int> get(std::string &s, int n) {
    // s += std::string(n, ' ');
    std::vector<int> sa(n, 0), rk(n * 2, 0), tmp(n * 2, 0), cnt(n + 26, 0);
    
    // init sa
    for (int i = 0; i < n; i++) {
        cnt[s[i] - 'a']++;
    }
    for (int i = 1; i < 26; i++) {
        cnt[i] += cnt[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        sa[--cnt[s[i] - 'a']] = i;
    }
    // init rk
    rk[sa[0]] = 1;
    for (int i = 1, p = 1; i < n; i++) {
        rk[sa[i]] = (s[sa[i]] == s[sa[i - 1]] ? p : ++p);
    }

    // a -> b
    auto trans = [&](std::vector<int> &a, std::vector<int> &b, int d) -> void {
        std::fill(cnt.begin(), cnt.end(), 0);
        for (int i = 0; i < n; i++) {
            cnt[rk[i + d]]++;
        }
        for (int i = 1; i <= n; i++) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) {
            b[--cnt[rk[a[i] + d]]] = a[i];
        }
    };
    for (int k = 1; k < n; k <<= 1) {
        trans(sa, tmp, k), trans(tmp, sa, 0);

        tmp[sa[0]] = 1;
        for (int i = 1, p = 1; i < n; i++) {
            if (rk[sa[i]] > rk[sa[i - 1]] || rk[sa[i] + k] > rk[sa[i - 1] + k]) {
                p++;
            }
            tmp[sa[i]] = p;
        }
        rk = tmp;
    }
    return sa;
}

void solve()
{
    std::string s;
    std::cin >> s;
    int n = s.size();

    auto sa = get(s, n);
    for (int i = 0; i < n; i++) {
        std::cout << sa[i] << " \n"[i == n - 1];
    }

    Hash hash(s);
    std::vector h(n, 0);
    for (int i = 0; i < n; i++) {
        for (int l = 25; i != 0 && l >= 0; l--) {
            int len = h[i] + (1 << l);
            if (len <= n - std::max(sa[i], sa[i - 1])) {
                if (hash.get(sa[i], sa[i] + len) == hash.get(sa[i - 1], sa[i - 1] + len)) {
                    h[i] = len;
                }
            }
        }
        std::cout << h[i] << " \n"[i == n - 1];
    }
}

int main()
{
    // IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}