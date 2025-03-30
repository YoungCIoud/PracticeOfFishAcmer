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
constexpr int N = 1e4, Inf = 1e9;

// 0 : Uncertain, AKA Tie
// 1 : P
// 2 : N
int status[N];
int cntp[N]; // 每个状态有 4 个后继状态，如果 4 个后继状态都是 P，那当前状态就是 N
std::vector<int> g[N];
std::vector<int> ig[N];

int idx[10][10][10][10];

void solve()
{
    int a = 0, b = 0, c = 0, d = 0;
    std::cin >> a >> b >> c >> d;
    if (a > b) {
        std::swap(a, b);
    }
    if (c > d) {
        std::swap(c, d);
    }
    std::cout << status[idx[a][b][c][d]] << '\n';
}

int main()
{
    IOS;
    int _t = 1;
    std::cin >> _t;
    
    std::queue<int> q;
    auto push = [&](int u, int s) -> void {
        status[u] = s;
        q.push(u);
    };
    auto add = [&](int u, int a, int b, int c, int d) -> void {
        if (c > d) {
            std::swap(c, d);
        }
        int v = idx[a][b][c][d];
        assert(a <= b && c <= d);
        g[u].push_back(v);
        ig[v].push_back(u);
    };
    int cnt = 0;
    for (int a = 0; a < 10; a++) {
        for (int b = a; b < 10; b++) {
            for (int c = 0; c < 10; c++) {
                for (int d = c; d < 10; d++) {
                    int u = idx[a][b][c][d] = cnt++;
                    if (a == 0 && b == 0) {
                        push(u, 1);
                    }
                    else if (c == 0 && d == 0) {
                        push(u, 2);
                    }
                }
            }
        }
    }
    for (int a = 0; a < 10; a++) {
        for (int b = std::max(a, 1); b < 10; b++) {
            for (int c = 0; c < 10; c++) {
                for (int d = std::max(c, 1); d < 10; d++) {
                    int u = idx[a][b][c][d];
                    if (a) {
                        if (c) {
                            add(u, c, d, (a + c) % 10, b);
                        }
                        add(u, c, d, (a + d) % 10, b);
                    }
                    if (c) {
                        add(u, c, d, a, (b + c) % 10);
                    }
                    add(u, c, d, a, (b + d) % 10);
                }
            }
        }
    }
    
    while (not q.empty()) {
        int v = q.front();
        q.pop();

        if (status[v] == 2) {
            for (auto &u : ig[v]) {
                if (status[u] == 0) {
                    push(u, 1);
                }
            }
        }
        else {
            for (auto &u : ig[v]) {
                if (status[u] == 0 && ++cntp[u] == g[u].size()) {
                    push(u, 2);
                }
            }
        }
    }

    while (_t--)
    {
        solve();
    }

    sp();

    return 0;
}