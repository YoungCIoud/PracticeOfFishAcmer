#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5;
constexpr i64 Mod = 998244353;

class BIT {
public:
        BIT(int _n) {
                n = _n;
                tr.assign(n + 1, 0);
        }
        void add(int pos, int val) {
                for (int i = pos; i <= n; i += lowbit(i)) {
                        tr[i] += val;
                }
                return;
        }
        int sum(int l, int r) {
                return sum(r) - sum(l - 1);
        }
private:
        int n;
        std::vector<int> tr;
        int lowbit(int x) {
                return x & -x;
        }
        int sum(int x) {
                int res = 0;
                for (int i = x; i > 0; i -= lowbit(i)) {
                        res += tr[i];
                }
                return res;
        }
};


int main () {
        int n = 0;
        std::cin >> n;
        std::vector p(2, std::vector(n + 1, 0));
        for (int i = 0; i < 2; i++) {
                for (int j = 1; j <= n; j++) {
                        int x = 0;
                        std::cin >> x;
                        p[i][x] = j;
                }
        }
        long long ans = n;
        BIT a(n), b(n);
        for (int r = 1, l = 1; r <= n; r++) {
                while (a.sum(1, p[0][r]) != b.sum(1, p[1][r])) {
                        a.add(p[0][l], -1);
                        b.add(p[1][l], -1);
                        l++;
                }
                ans += 1ll * (r - l);
                // std::cout << l << ' ' << r << '\n';
                a.add(p[0][r], 1);
                b.add(p[1][r], 1);
        }
        std::cout << ans << '\n';
        system("pause");
        return 0;
}