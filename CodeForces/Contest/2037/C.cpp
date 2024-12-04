#include <bits/stdc++.h>

void solve() {
    int n = 0;
    std::cin >> n;
    if (n <= 4) {
        std::cout << -1 << '\n';
        return;
    }
    for (int i = 1; i <= n; i += 2) {
        if (i != 5) {
            std::cout << i << ' ';
        }
    }
    std::cout << "5 4 ";
    for (int i = 2; i <= n; i += 2) {
        if (i != 4) {
            std::cout << i << ' ';
        }
    }
    std::cout << '\n';
    return;
}

int main () {
    int t = 1;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}