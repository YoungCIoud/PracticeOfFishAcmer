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
constexpr int N = 1e5, M = 1e5, Inf = 1e9;

class Time {
public:
    int h, m, s;
    Time(int hh, int mm = 0, int ss = 0): h(hh), m(mm), s(ss) {}
    bool operator<=(Time &a) {
        if (h == a.h) {
            if (m == a.m) {
                return s <= a.s;
            }
            else {
                return m < a.m;
            }
        }
        else {
            return h < a.h;
        }
    }
};

Time work1l(7),  work1r(9);
Time work2l(18),  work2r(20);
Time napl(11), napr(13);
Time slp1l(22), slp1r(23, 59, 59);
Time slp2l(0), slp2r(1);

bool chk(Time &u, Time &x, Time &v) {
    return u <= x && x <= v;
}

void solve()
{
    int n = 0, h = 0, m = 0;
    std::cin >> n >> h >> m;
    std::map<std::string, bool> vwork, vslp, vnap;
    int work = 0, slp = 0, nap = 0;
    for (int i = 0; i < n; i++) {
        std::string id;
        int Y = 0, Mo = 0, D = 0;
        int H = 0, Mi = 0, S = 0;
        std::cin >> id;
        scanf("%d-%2d-%2d %2d:%2d:%2d", &Y, &Mo, &D, &H, &Mi, &S);
        if (Y == h && Mo == m) {
            Time t(H, Mi, S);
            if ((chk(work1l, t, work1r) || chk(work2l, t, work2r)) && not vwork[id]) {
                vwork[id] = true;
                work++;
            }
            else if (chk(napl, t, napr) && not vnap[id]) {
                vnap[id] = true;
                nap++;
            }
            else if ((chk(slp1l, t, slp1r) || chk(slp2l, t, slp2r)) && not vslp[id]) {
                vslp[id] = true;
                slp++;
            }
        }
    }
    std::cout << work << ' ' << nap << ' ' << slp << '\n';
    return;
}

int main()
{
    // IOS;
    int _t = 1;
    // std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }

    sp();

    return 0;
}