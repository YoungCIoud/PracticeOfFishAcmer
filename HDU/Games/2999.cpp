#include<bits/stdc++.h>
constexpr int N = 100, M = 1000, K = 1000;
std::vector<int> a(N + 5), sg(K + 5, 0);
std::bitset<K + 5> vis;
int n = 0;

void get() {
    for (int i = 1; i <= K; i++) {
        vis.reset();
        for (int j = 0; j < n && a[j] <= i; j++) {
            while (a[j] == a[j + 1]) {
                j++;
            }

            for (int k = 0; k <= i - a[j]; k++) {
                vis.set(sg[k] ^ sg[i - a[j] - k]);
            }
        }

        for (int j = 0; j <= K; j++) {
            if (vis[j] == false) {
                sg[i] = j;
                break;
            }
        }
    }
}

int main () {
    while ((std::cin >> n)) {
        for (int i = 0; i < n; i++) {
            std::cin >> a[i];
        }
        std::sort(a.begin(), a.begin() + n);
        a[n] = 0;
    
        get();

        int m = 0;
        std::cin >> m;
        while (m--) {
            int k = 0;
            std::cin >> k;
            puts(sg[k] != 0 ? "1" : "2");
        }
    }
}