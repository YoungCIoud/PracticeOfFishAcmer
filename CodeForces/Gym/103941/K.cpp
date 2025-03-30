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
constexpr int N = 1e5, L = 450; // 450 sqrt(2e5)
int to[N + 5], in[N + 5], d[N + 5];
int pre[L][N + 5], len[L], col[N + 5], cnt, idx[N + 5];

void dfs(int cur) {
    if (col[cur] == 0) {
        dfs(to[cur]);
        col[cur] =  col[to[cur]]; // 染色
        d[cur] = d[to[cur]] + 1;
        pre[col[cur]][d[cur]]++;
    }
    return;
}

void solve()
{
    int n = 0;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        int f = 0;
        std::cin >> f;
        to[i] = f;
        in[f]++;
    }

    std::queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (in[i] == 0) {
            q.push(i);
        }
    }

    while (not q.empty()) {
        int cur = q.front();
        q.pop();
        if (--in[to[cur]] == 0) {
            q.push(to[cur]);
        }
    }

    // 维护环
    for (int i = 1; i <= n; i++) {
        if (in[i] != 0) {
            // 确定颜色，环长相同的基环树颜色相同
            int cur = i, l = 0;
            do {
                l++;
                in[cur] = 0;
                d[cur] = 0;
                cur = to[cur];
            } while (cur != i);
            int c = idx[l];
            if (c == 0) {
                c = idx[l] = ++cnt;
                len[c] = l;
            }

            pre[c][0] += l;
            do
            {
                col[cur] = c;
                cur = to[cur];
            } while (cur != i);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (col[i] == 0) {
            dfs(i);
        }
    }
    for (int i = 1; i <= cnt; i++) {
        for (int j = 1; j <= n; j++) {
            pre[i][j] += pre[i][j - 1];
        }
    }

    int qr = 0;
    std::cin >> qr;
    while (qr--) {
        i64 a = 0, b = 0;
        std::cin >> a >> b;

        if (a == b) {
            std::cout << n << '\n';
            continue;
        }
        int ans = 0;
        for (int l = 1; l <= cnt; l++) {
            if (a % len[l] == b % len[l]) {
                ans += pre[l][std::min({ a, b, i64(n) })];
            }
        }
        std::cout << ans << '\n';
    }
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

    sp();

    return 0;
}

/*
6
1 1 4 5 1 4
5
1 919810
19 19810
191 9810
1919 810
19198 10
*/