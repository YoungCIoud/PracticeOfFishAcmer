#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 Inf = 1e15, Mod = 1e9 + 7;
constexpr int N = 1e6;
std::string s, t;
int tr[N + 5][26], tot = 1;
int fail[N + 5], len[N + 5], deep[N + 5];

int getfail(int u, int i) {
    while (i - len[u] - 1 < 0 || s[i - len[u] - 1] != s[i]) {
        u = fail[u];
    }
    return u;
}

void solve() {
    std::cin >> s >> t;
    std::reverse(s.begin(), s.end());

    std::vector num(s.length(), 0);
    fail[0] = 1;
    len[1] = -1;
    for (int i = 0, cur = 0; i < s.length(); i++) {
        int c = s[i] - 'a';
        int pos = getfail(cur, i);
        if (tr[pos][c] == 0) {
            fail[++tot] = tr[getfail(fail[pos], i)][c];
            tr[pos][c] = tot, len[tot] = len[pos] + 2, deep[tot] = deep[fail[tot]] + 1;
        }
        cur = tr[pos][c];
        num[i] = deep[cur];
    }

    std::string st = t + "*" + s;
    int n = st.length();
    std::vector z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r && z[i - l] < r - i + 1) {
            z[i] = z[i - l];
        }
        else {
            z[i] = std::max(0, r - i + 1);
            while (i + z[i] < n && st[z[i]] == st[i + z[i]]) {
                z[i]++;
            }
            r = i + z[i] - 1, l = i;
        }
    }
    i64 ans = 0;
    for (int i = 1; i < s.length(); i++) {
        ans += 1ll * num[i - 1] * z[t.length() + 1 + i];
    }
    std::cout << ans << '\n';
    return;
}

int main () {
    std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
    int _t = 1;
    while (_t--) {
        solve();
    }
    system("pause");
    return 0;
}