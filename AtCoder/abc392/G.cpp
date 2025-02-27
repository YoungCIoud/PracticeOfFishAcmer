#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
#else
    #define debug(...)
    #define sp()
    #define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 1e5, M = 1e6, Inf = 1e9;

std::vector<int> idx(M << 2);
void fft(int len, std::vector<std::complex<double>> &A, int inv) {
    for (int i = 1; i < len; i++) {
        if (i < idx[i]) {
            std::swap(A[i], A[idx[i]]);
        }
    }

    for (int mid = 1; mid < len; mid <<= 1) {
        std::complex<double> unit(cos(M_PI / mid), inv * sin(M_PI / mid));
        for (int l = 0; l < len; l += (mid << 1)) {
            std::complex<double> w(1.0, 0.0);
            for (int i = 0; i < mid; i++, w *= unit) {
                std::complex<double> x(A[i | l]), y(w * A[i | l | mid]);
                A[i | l] = x + y;
                A[i | l | mid] = x - y;
            }
        }
    }

    for (int i = 0; inv == -1 && i < len; i++) {
        A[i] /= len;
    }
    return;
}

std::vector<i64> converlution(std::vector<i64> &a, std::vector<i64> &b) {
    int la = a.size() - 1, lb = b.size() - 1;
    int len = 1;
    // 长度是 2 的幂且必须大于最高次数
    while (len <= la + lb) {
        len <<= 1;
    }
    
    for (int l = 1, r = 1, bit = len >> 1; l < len; l <<= 1, bit >>= 1) {
        for (int i = 0; i < l; i++) {
            idx[r++] = idx[i] | bit;
        }
    }

    std::vector<std::complex<double>> A(len);
    for (int i = 0; i < len; i++) {
        A[i] = std::complex<double>(i <= la ? a[i] : 0.0, i <= lb ? b[i] : 0.0);
    }
    fft(len, A, 1);
    for (int i = 0; i < len; i++) {
        A[i] = A[i] * A[i];
    }
    fft(len, A, -1);

    std::vector res(la + lb + 1, 0ll);
    for (int i = 0; i <= la + lb; i++) {
        res[i] = i64(A[i].imag() / 2.0 + 0.5);
    }
    return res;
}

void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector p(M + 1, 0ll);
    for (int i = 0; i < n; i++) {
        int a = 0;
        std::cin >> a;
        p[a] = 1;
    }

    i64 res = 0;
    auto q = converlution(p, p);
    for (int i = 1; i <= M; i++) {
        if (p[i] == 1) {
            res += (q[2 * i] - 1) / 2;
        }
    }
    std::cout << res << '\n';
    return;
}

int main()
{
    IOS;
    int _t = 1;
    // std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }

    sp();

    return 0;
}