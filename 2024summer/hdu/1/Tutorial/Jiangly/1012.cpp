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

struct Comb {
    int n;
    std::vector<Z> _fac;
    std::vector<Z> _invfac;
    std::vector<Z> _inv;
    
    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    Comb(int n) : Comb() {
        init(n);
    }
    
    void init(int m) {
        m = std::min<i64>(m, Z::getMod() - 1);
        if (m <= n) return;
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);
        
        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _invfac[m] = _fac[m].inv();
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
            _inv[i] = _invfac[i] * _fac[i - 1];
        }
        n = m;
    }
    
    Z fac(int m) {
        if (m > n) init(2 * m);
        return _fac[m];
    }
    Z invfac(int m) {
        if (m > n) init(2 * m);
        return _invfac[m];
    }
    Z inv(int m) {
        if (m > n) init(2 * m);
        return _inv[m];
    }
    Z binom(int n, int m) {
        if (n < m || m < 0) return 0;
        return fac(n) * invfac(m) * invfac(n - m);
    }
} comb;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> vx, vy;
    std::vector<int> x1(n), x2(n), y1(n), y2(n);
    for (int i = 0; i < n; i++) {
        std::cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
        vx.push_back(x1[i]);
        vx.push_back(x2[i]);
        vy.push_back(y1[i]);
        vy.push_back(y2[i]);
    }
    std::sort(vx.begin(), vx.end());
    std::sort(vy.begin(), vy.end());
    vx.erase(std::unique(vx.begin(), vx.end()), vx.end());
    vy.erase(std::unique(vy.begin(), vy.end()), vy.end());
    
    const int nx = vx.size(), ny = vy.size();
    std::vector f(nx, std::vector<int>(ny));
    for (int i = 0; i < n; i++) {
        x1[i] = std::lower_bound(vx.begin(), vx.end(), x1[i]) - vx.begin();
        x2[i] = std::lower_bound(vx.begin(), vx.end(), x2[i]) - vx.begin();
        y1[i] = std::lower_bound(vy.begin(), vy.end(), y1[i]) - vy.begin();
        y2[i] = std::lower_bound(vy.begin(), vy.end(), y2[i]) - vy.begin();
        f[x1[i]][y1[i]]++;
        f[x1[i]][y2[i]]--;
        f[x2[i]][y1[i]]--;
        f[x2[i]][y2[i]]++;
    }
    
    for (int i = 0; i < nx; i++) {
        for (int j = 1; j < ny; j++) {
            f[i][j] += f[i][j - 1];
        }
    }
    for (int i = 1; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            f[i][j] += f[i - 1][j];
        }
    }
    
    std::vector<Z> a(n + 1);
    for (int i = 0; i + 1 < nx; i++) {
        for (int j = 0; j + 1 < ny; j++) {
            a[f[i][j]] += Z(vx[i + 1] - vx[i]) * (vy[j + 1] - vy[j]);
        }
    }
    
    for (int k = 1; k <= n; k++) {
        Z ans = 0;
        for (int i = 0; i <= n; i++) {
            ans += (comb.binom(n, k) - comb.binom(n - i, k)) * a[i];
        }
        ans /= comb.binom(n, k);
        std::cout << ans << "\n";
    }
    
    return 0;
}