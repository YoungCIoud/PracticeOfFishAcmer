#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
    // #define cout cout << ">>>\t"
#else
    #define debug(...)
    #define sp()
    #define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 1e6, M = 1e5, Inf = 1e9;
std::vector<int> P;
bool vis[N + 1];

void solve()
{
    for (int i = 2; i <= N; i++) {
        if (not vis[i]) {
            // std::cout << i << ' ';
            P.push_back(i);
        }

        for (auto &p : P) {
            if (i * p > N) {
                break;
            }
            vis[i * p] = true;
            if (i % p == 0) {
                break;
            }
        }
    }
    // std::cout << P.size() << '\n';
    int n = 0;
    std::cin >> n;
    std::unordered_map<int, std::vector<int>> pos;
    for (int i = 0; i < n; i++) {
        int a = 0;
        std::cin >> a;
        for (int j = 0; P[j] * P[j] <= a; j++) {
            if (a % P[j] == 0) {
                pos[P[j]].push_back(i);
                while (a % P[j] == 0) {
                    a /= P[j];
                }
            }
        }
        if (a != 1) {
            pos[a].push_back(i);
        }
    }

    auto cnt = [&](int len) -> i64 {
        return 1ll * len * (len + 1) / 2ll;
    };
    i64 ans = pos.size() * cnt(n);
    for (auto &[p, arr] : pos) {
        ans -= cnt(arr[0]);
        ans -= cnt(n - arr.back() - 1);
        for (int i = 1; i < arr.size(); i++) {
            ans -= cnt(arr[i] - arr[i - 1] - 1);
        }
    }
    std::cout << ans << '\n';
}

int main()
{
    IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    sp();

    return 0;
}