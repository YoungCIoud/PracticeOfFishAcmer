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
constexpr int N = 2e5, MAX = 1e9, Inf = 1e9;
i64 a[N + 5], b[N + 5], top;
i64 ans[N + 5];
void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::sort(a, a + n);
    for (int i = 0; i < m; i++) {
        std::cin >> b[i];
    }
    std::sort(b, b + m);

    top = 0;
    i64 cur = 0;
    int pa = 0, pb = 0;
    int la = n, lb = m;
    while (true) {
        // 上下两个都可以作为底边
        if (la >= 2 && lb >= 2) {
            int va = a[n - pa - 1] - a[pa];
            int vb = b[m - pb - 1] - b[pb];
            if (va >= vb) {
                cur += va;
                pa++, la -= 2;
                lb--;
            }
            else {
                cur += vb;
                pb++, lb -= 2;
                la--;
            }
            ans[top++] = cur;
        }

        // 只有一个可以作为底边
        else if (la >= 2 && lb == 1) {
            cur += a[n - pa - 1] - a[pa];
            pa++, la -= 2;
            lb--;
            ans[top++] = cur;
        }
        else if (la == 1 && lb >= 2) {
            cur += b[m - pb - 1] - b[pb];
            pb++, lb -= 2;
            la--;
            ans[top++] = cur;
        }

        // 两个都做不了底边，但可撤销
        else if (la >= 3 && pb >= 1) {
            cur += b[pb - 1] - b[m - pb];
            pb--;

            cur += a[n - pa - 1] + a[n - pa - 2] - a[pa] - a[pa + 1];
            la -= 3;
            pa += 2;
            ans[top++] = cur;
        }
        else if (lb >= 3 && pa >= 1) {
            cur += a[pa - 1] - a[n - pa];
            pa--;

            cur += b[m - pb - 1] + b[m - pb - 2] - b[pb] - b[pb + 1];
            lb -= 3;
            pb += 2;
            ans[top++] = cur;
        }

        else {
            break;
        }
    }

    std::cout << top << '\n';
    for (int i = 0; i < top; i++) {
        std::cout << ans[i] << ' ';
    }
    std::cout << '\n';
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


    return 0;
}
/*
5
1 3
0
0 1 -1
2 4
0 100
-100 -50 0 50
2 4
0 1000
-100 -50 0 50
6 6
20 1 27 100 43 42
100 84 1 24 22 77
8 2
564040265 -509489796 469913620 198872582 -400714529 553177666 131159391 -20796763
-1000000000 1000000000

1
2
2
150 200
2
1000 200
4
99 198 260 283
2
2000000000 2027422256
*/