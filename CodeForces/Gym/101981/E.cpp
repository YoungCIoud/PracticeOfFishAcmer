#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 Inf = 1e15, Mod = 1e9 + 7;
constexpr int N = 1e6;

int n, k;
std::vector stk(N, char{});
std::vector len(N, 0);
std::string trans(const std::string &s) {
    int top = 0;
    len[0] = 1;
    for (auto &c : s) {
        stk[top] = c;
        top && ((len[top] = (c == stk[top - 1] ? len[top - 1] + 1 : 1), false) || (len[top] == k && (top -= k)));
        top++;
    }

    std::string t;
    for (int i = 0; i < top; i++) {
        t.push_back(stk[i]);
    }
    // std::cout << t << '\n';
    return t;
}

void solve() {
    std::string s1, s2;
    std::cin >> n >> k >> s1 >> s2;

    puts((k == 1 || trans(s1) == trans(s2)) ? "Yes" : "No");
    return;
}

int main () {
    int _t = 1;
    // std::cin >> _t;
    while (_t--) {
        solve();
    }
    system("pause");
    return 0;
}