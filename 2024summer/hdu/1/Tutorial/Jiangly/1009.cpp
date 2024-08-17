#include <bits/stdc++.h>

using i64 = long long;
template<class T>
constexpr T power(T a, i64 b) {
    T res {1};
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

constexpr i64 mul(i64 a, i64 b, i64 p) {
    i64 res = a * b - i64(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
}

template<i64 P>
struct MInt {
    i64 x;
    constexpr MInt() : x {0} {}
    constexpr MInt(i64 x) : x {norm(x % getMod())} {}
    
    static i64 Mod;
    constexpr static i64 getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(i64 Mod_) {
        Mod = Mod_;
    }
    constexpr i64 norm(i64 x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr i64 val() const {
        return x;
    }
    constexpr MInt operator-() const {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MInt inv() const {
        return power(*this, getMod() - 2);
    }
    constexpr MInt &operator*=(MInt rhs) & {
        if (getMod() < (1ULL << 31)) {
            x = x * rhs.x % int(getMod());
        } else {
            x = mul(x, rhs.x, getMod());
        }
        return *this;
    }
    constexpr MInt &operator+=(MInt rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MInt &operator-=(MInt rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MInt &operator/=(MInt rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MInt operator*(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MInt operator+(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MInt operator-(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MInt operator/(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MInt &a) {
        i64 v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MInt lhs, MInt rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MInt lhs, MInt rhs) {
        return lhs.val() != rhs.val();
    }
    friend constexpr bool operator<(MInt lhs, MInt rhs) {
        return lhs.val() < rhs.val();
    }
};

template<>
i64 MInt<0>::Mod = 998244353;

constexpr int P = 998244353;
using Z = MInt<P>;

Z get(std::string n, std::string R, bool eq) {
    const int k = R.size();
    std::vector dp(2, std::vector(k + 2, std::array<Z, 10>{}));
    bool first = true;
    for (auto c : n) {
        int d = c - '0';
        std::vector ndp(2, std::vector(k + 2, std::array<Z, 10>{}));
        for (int x = 1; x <= (first ? d : 9); x++) {
            ndp[!first || x < d][1][x] += 1;
            ndp[!first || x < d][0][0] += 1;
        }
        for (int l = 0; l < 2; l++) {
            for (int len = 0; len <= k + 1; len++) {
                for (int lst = 0; lst < 10; lst++) {
                    if (dp[l][len][lst] == 0) {
                        continue;
                    }
                    Z val = dp[l][len][lst];
                    for (int x = 0; x <= (l ? 9 : d); x++) {
                        ndp[l || x < d][len][lst] += val;
                        if (len == 0 || (len <= k && x != lst && (x > lst) == (R[len - 1] == '<'))) {
                            ndp[l || x < d][len + 1][x] += val;
                        }
                    }
                }
            }
        }
        first = false;
        dp = std::move(ndp);
    }
    Z ans = 0;
    for (int i = 0; i < 10; i++) {
        ans += dp[1][k + 1][i];
        if (eq) {
            ans += dp[0][k + 1][i];
        }
    }
    return ans;
}

void solve() {
    std::string l, r;
    std::cin >> l >> r;
    
    std::string R;
    std::cin >> R;
    
    Z ans = get(r, R, true) - get(l, R, false);
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