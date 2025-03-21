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
#define double long double

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 1e9 + 7;
constexpr int N = 2e5, MAX = 1e9;
std::multiset<int> s;

bool find(int x) {
    if (s.empty() || x < (*s.begin())) {
        return false;
    }
    else if (s.count(x)) {
        s.erase(s.find(x));
        return true;
    }
    else {
        return find(x >> 1) && find(x + 1 >> 1);
    }
}

bool solve() {
    s.clear();
    int n = 0, m = 0;
    std::cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int a = 0;
        std::cin >> a;
        s.insert(a);
    }

    bool ok = true;
    for (int i = 0; i < m; i++) {
        int b = 0;
        std::cin >> b;
        if (ok) {
            ok = find(b);
        }
    }
    return ok && s.empty();
}

int main()
{
    IOS;
    int _t = 1;
    std::cin >> _t;

    while (_t--)
    {
        std::cout << (solve() ? "Yes" : "No") << '\n';
    }

    return 0;
}
