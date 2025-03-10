#include <bits/stdc++.h>

#define IOS \
std::ios::sync_with_stdio(false);\
std::cin.tie(nullptr);\
std::cout.tie(nullptr);

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, inv2 = 499122177, Inf = 1e15;
constexpr int N = 1e5, M = 22;

class st {
private:
    std::vector<std::array<i64, M>> a;
public:
    st() {
        insert(0);
    }
    void insert(i64 val) {
        a.push_back(std::array<i64, M>{});
        int R = a.size() - 1;
        a[R][0] = val;
        for (int l = 1; l < M; l++) {
            if (R - (1 << l) + 1>= 0) {
                a[R][l] = std::max(a[R][l - 1], a[R - (1 << l - 1)][l - 1]);
            }
        }
    }

    i64 ask(int l, int r) {
        int len = log2(r - l + 1);
        return std::max(a[l + (1 << len) - 1][len], a[r][len]);
    }
};

void solve() {
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector a(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    std::vector g(1 << m, 0ll);
    for (auto &i : g) {
        std::cin >> i;
    }

    std::vector nxt(n + 1, std::vector(m, std::array<int, 2>{ 0, 0 }));
    for (int bit = 0; bit < m; bit++) {
        for (int i = 1; i <= n; i++) {
            int b = (a[i] >> bit) & 1;
            nxt[i][bit][b] = i; 
            nxt[i][bit][b ^ 1] = nxt[i - 1][bit][b ^ 1];
        }
    }

    // 以第 i 个数为右端点r，以第 jump[i][j][0] 个数为左端点l时，f(l, r) 第一次变到 jump[i][j][1]
    std::vector jump(n + 1, std::vector(m + 2, std::array<int, 2>{ 0, 0 }));
    std::priority_queue<int> q;
    for (int i = 1; i <= n; i++) {
        jump[i][0] = { i, 0 };
        for (int j = 0; j < m; j++) {
            q.push(nxt[i][j][((a[i] >> j) & 1) ^ 1]);
        }
        int k = 1, res = 0;
        while (not q.empty()) {
            int cur = q.top();
            while (not q.empty() && q.top() == cur) {
                q.pop();
            }
            if (cur == 0) {
                break;
            }
            for (int j = 0; j < m; j++) {
                if (((a[i] ^ a[cur]) >> j) & 1) {
                    res |= (1 << j);
                }
            }
            jump[i][k++] = { cur, res };
        }
    }
    
    st dp;
    for (int i = 1; i <= n; i++) {
        i64 tmp = -Inf;
        int k = 0;
        while (k <= m && jump[i][k][0]) {
            auto &[r, val] = jump[i][k++];
            tmp = std::max(tmp, dp.ask(jump[i][k][0], r - 1) + g[val]);
        }
        dp.insert(tmp);
    }

    std::cout << dp.ask(n, n) << '\n';
    return;
}

int main () {
    IOS

    int _t = 1;
    std::cin >> _t;
    while (_t--) {
        solve();
    }

    //system("pause");
    return 0;
}
