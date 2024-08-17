#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;
    
    i64 ans = 1;
    for (int i = 0; i < k; i++) {
        if (n >> i & 1) {
            ans *= 3;
        }
    }
    ans <<= 2 * k;
    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}