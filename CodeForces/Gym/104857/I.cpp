#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3e6;
constexpr i64 Mod = 998244353;

int cnt[60][60][5];
int f['z' + 5], g[52];
void pre(int n) {
        for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                        int m = i * j;
                        if (m == 0) {
                                cnt[n][0][0]++;
                        }
                        else {
                                int k = 0;
                                while (m != 0) {
                                        int t = m % n;
                                        cnt[n][t][k++]++;
                                        m /= n;
                                        if (t == 1 && m != 0) {
                                                cnt[n][m][2]++;
                                        }
                                        if (m == 1) {
                                                cnt[n][t][3]++;
                                        }
                                        if (m == 3) {
                                            cnt[n][t][4]++;
                                        }
                                }
                        }
                }
        }
}

int main () {
        for (int i = 2; i <= 52; i++) {
                pre(i);
        }
        for (int i = 0; i < 26; i++) {
                f['a' + i] = i;
                g[i] = 'a' + i;
                f['A' + i] = i + 26;
                g[i + 26] = 'A' + i;
        }
        int t = 0;
        std::cin >> t;
        while (t--) {
                int n = 0;
                std::cin >> n;
                std::vector num(n * n, std::string{});
                std::vector h(n, std::vector(5, 0));
                for (auto &s : num) {
                        std::cin >> s;
                        std::reverse(s.begin(), s.end());
                        for (int i = 0; i < s.size(); i++) {
                                h[f[s[i]]][i]++;
                        }
                }

                std::vector ans(n, -1);

                for (int i = 0; i < n; i++) {
                        if (h[i][0] == cnt[n][1][0] && h[i][1] == cnt[n][1][1]) {
                                ans[1] = i;
                        }
                        if (h[i][0] == cnt[n][3][0] && h[i][1] == cnt[n][3][1]) {
                                ans[3] = i;
                        }
                }
                for (auto &s : num) {
                        if (s.size() == 2) {
                                if (s[0] == g[ans[1]] && s.size() == 2) {
                                                h[f[s[1]]][2]++;
                                }
                                if (s[1] == g[ans[1]]) {
                                                h[f[s[0]]][3]++;
                                }
                                if (s[1] == g[ans[3]]) {
                                                h[f[s[0]]][4]++;
                                }
                        }
                }
                for (int i = 0; i < n; i++) {
                        for (int j = 0; j < n; j++) {
                                bool ok = true;
                                for (int k = 0; k < 5; k++) {
                                        if (cnt[n][i][k] != h[j][k]) {
                                                ok = false;
                                                break;
                                        }
                                }
                                if (ok) {
                                        ans[i] = j;
                                        break;
                                }
                        }
                }
                for (int i = 0; i < n; i++) {
                        std::cout << char(g[ans[i]]);
                }
                std::cout << '\n';
        }
        system("pause");
        return 0;
}