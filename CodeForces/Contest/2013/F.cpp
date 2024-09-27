#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 2e5, M = 1e5;
class ST {
public:
    ST(std::vector<int> &a) {
        n = a.size();
        st.assign(n, std::vector<int>(20, 0));
        for (int i = 0; i < n; i++) {
            st[i][0] = a[i];
        }
        for (int l = 1; l < 20; l++) {
            for (int i = 0; i + (1 << l) <= n; i++) {
                st[i][l] = std::max(st[i][l - 1], st[i + (1 << (l - 1))][l - 1]);
            }
        }
    }
    int quiry(int l, int r) {
        if (l > r) return -1;
        int len = log2(r - l + 1);
        return std::max(st[l][len], st[r - (1 << len) + 1][len]);
    }
private:
    std::vector<std::vector<int>> st;
    int n;
};

std::vector<int> g[N + 5], p;
bool is_p[N + 5];
void init(int n) {
    p.clear();
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        is_p[i] = false;
    }
}

void getpath(int cur, int fa) {
    if (cur == 1) {
        is_p[cur] = true;
        p.push_back(cur);
        return;
    }

    for (auto &to : g[cur]) {
        if (to != fa) {
            getpath(to, cur);

            if (not p.empty()) {
                is_p[cur] = true;
                p.push_back(cur);
                break;
            }
        }
    }
}

int dfs(int cur, int fa) {
    int res = 1;
    for (auto &to : g[cur]) {
        if (to != fa) {
            res = std::max(res, dfs(to, cur) + 1);
        }
    }
    return res;
}

void solve() {
    int n = 0;
    std::cin >> n;
    init(n);

    for (int i = 0; i < n - 1; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    int s = 0;
    std::cin >> s >> s;
    // 找到从1到s的路径
    getpath(s, s);
    int len = p.size();
    // 路径上第i个点向外最长链的长度
    std::vector<int> d(len, 1);
    for (int i = 0; i < len; i++) {
        for (auto &to : g[p[i]]) {
            if (!is_p[to]) {
                d[i] = std::max(d[i], dfs(to, p[i]) + 1);
            }
        }
    }
    std::vector<int> da(d), db(d);
    for (int i = 0; i < len; i++) {
        da[i] += i;
        db[i] += len - 1 - i;
    }
    ST A(da), B(db);

    int win = true;
    for (int i = 0, j = len - 1; i < j ; i++, j--) {
        if (da[i] > B.quiry(i + 1, j)) {
            win = true;
            break;
        }
        else if (i + 1 == j) {
            win = false;
            break;
        }

        if (db[j] >= A.quiry(i + 1, j - 1)) {
            win = false;
            break;
        }
        else if (i + 1 == j - 1) {
            win = true;
            break;
        }
    }

    std::cout << (win ? "Alice" : "Bob") << '\n';
}

int main() {
    //IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}