#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 6e6;
constexpr i64 Mod = 998244353;
std::string s;
std::vector<int> g[N + 5];
int tr[N + 5][10], tot = 1;
int fail[N + 5], len[N + 5];
int cnt[N + 5];

int getfail(int u, int i) {
        while (i - len[u] - 1 < 0 || s[i - len[u] - 1] != s[i]) {
                u = fail[u];
        }
        return u;
}

int dfs(int cur) {
        for (auto &to : g[cur]) {
                cnt[cur] += dfs(to);
        }
        return cnt[cur];
}

int main () {
        int n = 0;
        std::cin >> n >> s;
        s += s;
        len[1] = -1;
        fail[0] = 1;
        for (int i = 0, cur = 0; i < 2 * n; i++) {
                int pos = getfail(cur, i);
                int num = s[i] - '0';
                if (tr[pos][num] == 0) {
                        tot++;
                        fail[tot] = tr[getfail(fail[pos], i)][num];
                        tr[pos][num] = tot, len[tot] = len[pos] + 2;
                }
                cur = tr[pos][num];
                if (i >= n) {
                    cnt[cur]++;
                }
        }

        // build fail tree
        for (int i = 2; i <= tot; i++) {
                g[fail[i]].push_back(i);
        };
        dfs(0);
        i64 ans = 0;
        for (int i = 2; i <= tot; i++) {
                if (len[i] <=n) {
                        (ans += 1ll * cnt[i] * cnt[i] % Mod * len[i] % Mod) %= Mod;
                }
        }
        std::cout << ans << '\n';
        return 0;
}