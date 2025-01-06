#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 Inf = 1e15, Mod = 1e9 + 7;
constexpr int N = 20, M = 50000;

void solve() {
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::string s;
    for (int i = 0; i < n; i++) {
        std::cin >> s;
    }
    s = "ULRD";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << s[i];
        }
    }

    srand(20050330);
    for (int i = 0; i < M - 80; i++) {
        std::cout << s[rand() % 4];
    }
}

int main () {
    int _t = 1;
    while (_t--) {
        solve();
    }

    system("pause");
    return 0;
}