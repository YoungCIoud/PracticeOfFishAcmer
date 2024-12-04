#include <bits/stdc++.h>

void sovle () {
    int k = 0;
    std::cin >> k;
    std::vector vis(k + 1, false);
    int ans = 0;
    for (int i = 0; i < k; i++) {
        int a = 0;
        std::cin >> a;
        if ((k - 2) % a == 0 && vis[(k - 2) / a]) {
            ans = a;
        }
        vis[a] = true;
    }
    std::cout << ans << ' ' << (k - 2) / ans << '\n';
    return;
}

int main () {
    int t = 1;
    std::cin >> t;
    while (t--) {
        sovle();
    }
    return 0;
}