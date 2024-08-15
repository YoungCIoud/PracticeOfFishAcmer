#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i128 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

std::istream& operator>>(std::istream& in, ary<i128, 2>& num) {
    str s;
    std::cin >> s;
    int n = s.size();
    n >>= 1;

    auto& [h, l] = num;
    h = 0, l = 0;
    for (int i = 0; i < n; i++)
    {
        h *= (i128)10;
        h += (i128)(s[i] - '0');
    }

    for (int i = n; i < s.size(); i++)
    {
        l *= (i128)10;
        l += (i128)(s[i] - '0');
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, __int128& num) {
    str s{};
    if (num == (i128)0) s += "0";
    while (num)
    {
        s += '0' + num % (i128)10;
        num /= (i128)10;
    }
    std::reverse(s.begin(), s.end());
    out << s;
    return out;
}

void solve()
{
    int n = 0;
    std::cin >> n;
    i128 mx = 0;
    n /= 2;
    for (int i = 0; i < n; i++)
    {
        mx *= 10ll;
        mx += 9ll;
    }

    ary<i128, 2> L{}, R{};
    std::cin >> L >> R;

    auto cnt = [=](i128 x) -> i128
    {
        if (x < 0) return 0;

        i128 l = 0, r = sqrt(x) + 1;
        while (l <= r)
        {
            i128 m = l + r >> 1;
            if (m * m <= x) l = m + 1;
            else r = m - 1;
        }
        //std::cout << x << " " << l << '\n';
        return l;
    };


    i128 ans = 0;
    if (R[0] != L[0])
    {   
        if ((cnt(L[0]) - 1) * (cnt(L[0]) - 1) == L[0]) ans += cnt(mx) - cnt(L[1] - 1);
        if ((cnt(R[0]) - 1) * (cnt(R[0]) - 1) == R[0]) ans += cnt(R[1]);

        ans += cnt(mx) * (cnt(R[0] - 1) - cnt(L[0]));
    }
    else
    {
         if ((cnt(L[0]) - 1) * (cnt(L[0]) - 1) == L[0]) ans = cnt(R[1]) - cnt(L[1] - 1);
    }
    std::cout << ans << '\n';
}

int main()
{
    //IOS;
    int t = 1;
    //std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}