#include <bits/stdc++.h>

int main() {
    std::vector cnt(4, 0);
    for (int i = 0; i < 4; i++) {
        int a = 0;
        std::cin >> a;
        cnt[a - 1]++;
    }
    int ans = 0;
    for (int i = 0; i < 4; i++) {
        ans += cnt[i] / 2;
    }
    std::cout << ans << '\n';
    return 0;
}