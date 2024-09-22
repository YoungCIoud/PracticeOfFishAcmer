#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 2e5, M = 1e5;

void solve()
{
    int n = 0;
    std::cin >> n;
    std::map<int, int> f;
    for (int i = 1; i <= n; i++) {
        int x = 0;
        std::cin >> x;
        f[i] = x - i;
    }
    // 缩点, 只保留每块的第一个点
    for (int i = 1; i <= n; i++) {
        if (f.count(i)) {
            auto it = f.find(i);
            while (true) {
                auto nxt = std::next(it);
                if (nxt == f.end() || nxt->second != it->second) {
                    break;
                }
                f.erase(nxt);
            }
        }
    }

    int q = 0;
    std::cin >> q;
    i64 ans = 0;
    while (q--) {
        int idx = 0, tar = 0;
        std::cin >> idx >> tar;
        tar -= idx;
        auto it = std::prev(f.upper_bound(idx));
        int pos = it->second;
        
        // 不移
        if (pos == tar) {
            continue;
        }
        // 右移
        if (pos < tar) {
            f[idx] = tar;
            it = f.find(idx);
            while (true) {
                auto nxt = std::next(it);
                if (nxt == f.end()) {
                    ans += 1ll * (tar - pos) * (n - idx + 1);
                    break;
                }
                if (nxt->second > tar) {
                    ans += 1ll * (tar - pos) * (nxt->first - idx);
                    break;
                }
                ans += 1ll * (nxt->second - pos) * (nxt->first - idx);
                pos = nxt->second;
                f.erase(nxt);
            }
        }
        // 左移
        else {
            // idx后形成一个新的块
            if (idx < n && f.count(idx + 1) == false) {
                f[idx + 1] = pos;
            }
            while (true) {
                if (it == f.begin()) {
                    ans += 1ll * (pos - tar) * idx;
                    break;
                }
                auto prv = std::prev(it);
                if (prv->second < tar) {
                    ans += 1ll * (pos - tar) * (idx - it->first + 1);
                    break;
                }
                ans += 1ll * (pos - prv->second) * (idx - it->first + 1);
                pos = prv->second;
                f.erase(it);
                it = prv;
            }
            it->second = tar;
        }
    }
    std::cout << ans << '\n';
}

int main()
{
    //IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}