#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 Mod = 1e9 + 7;
constexpr int N = 1e5, M = 1e9, T = 100;
std::vector<int> pri;
bool vis[N];

std::mt19937_64 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

int main() {
    for (int i = 2; i * i < N; i++) {
        if (not vis[i]) {
            pri.push_back(i);
        }

        for (auto &p : pri) {
            int d = p * i;
            if (d * d >= N) {
                break;
            }
            vis[d] = true;
            if (i % p == 0) {
                break;
            }
        }
    }

    int n = 0;
    std::cin >> n;
    std::vector a(n, 0);
    for (auto &i : a) {
        std::cin >> i;
    }

    if (n == 1) {
        std::cout << a[0] << ' ' << 2 << '\n';
        return 0;
    }

    std::array<int, 3> ans = { a[0], 2, 0 };
    for (int t = 0; t < T; t++) {
        int x = a[rnd() % n], y = 0;
        do {
            y = a[rnd() % n];
        } while (x == y);

        int d = std::abs(x - y);
        for (auto &p : pri) {
            if (p * p > d) {
                break;
            }
            if (d % p == 0) {
                while (d % p == 0) {
                    d /= p;
                }

                int cnt = 0;
                for (auto &i : a) {
                    if ((x - i) % p == 0) {
                        cnt++;
                    }
                }
                if (cnt > ans[2]) {
                    ans = { x % p, p, cnt };
                }

            }
        }

        if (d != 1) {
            int cnt = 0;
            for (auto &i : a) {
                if ((x - i) % d == 0) {
                    cnt++;
                }
            }
            if (cnt > ans[2]) {
                ans = { x % d, d, cnt };
            }
        }
    }

    std::cout << ans[0] << ' ' << ans[1] << '\n';
    return 0;
}