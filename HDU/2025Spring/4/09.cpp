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

constexpr int N = 15;

int n, q;
std::vector<int> use[5];
int R[N][5];

int ans[1 << N];

void solve()
{
    std::cin >> n >> q;
    for (auto &v : use) {
        int m = 0;
        std::cin >> m;
        v.clear();
        v.assign(m, 0);
        for (auto &i : v) {
            std::cin >> i;
            i--;
        }
    }
    std::fill(ans, ans + (1 << n), 0);
    for (auto &c0 : use[0]) {
        for (auto &c1 : use[1]) {
            for (auto &c2 : use[2]) {
                for (auto &c3 : use[3]) {
                    for (auto &c4 : use[4]) {
                        ans[(1 << c0) | (1 << c1) | (1 << c2) | (1 << c3) | (1 << c4)]++;
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 5; j++) {
            std::cin >> R[i][j];
        }
    }
    
    std::vector p(5, 0), b(0, 0);
    std::iota(p.begin(), p.end(), 0);
    for (int s = 0; s < (1 << n); s++) {
        if (std::__popcount(s) != 5) {
            ans[s] = 0;
        }
        else {
            b.clear();
            for (int i = 0; i < n; i++) {
                if (s >> i & 1) {
                    b.push_back(i);
                }
            }
            int mul = 0;
            do
            {
                if (R[b[0]][p[0]] && R[b[1]][p[1]] && R[b[2]][p[2]] && R[b[3]][p[3]] && R[b[4]][p[4]]) {
                    mul++;
                }
            } while (std::next_permutation(p.begin(), p.end()));
            ans[s] *= mul;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int s = 0; s < (1 << n); s++) {
            if (s >> i & 1) {
                ans[s] += ans[s ^ (1 << i)];
            }
        }
    }
    
    while (q--) {
        int m = 0, ban = 0;
        std::cin >> m;
        for (int i = 0; i < m; i++) {
            int x = 0;
            std::cin >> x;
            ban |= (1 << x - 1);
        }
        ban ^= (1 << n) - 1;
        std::cout << ans[ban] << '\n';
    }
    return;
}

int main()
{
    IOS;
    int _t = 1;
    std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }

    sp();

    return 0;
}