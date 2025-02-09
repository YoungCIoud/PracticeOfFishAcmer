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
std::vector g(3, std::string{});

bool chk() {
    for (int i = 0; i < 3; i++) {
        if (g[i] == "XXX") {
            return true;
        }
    }

    for (int j = 0; j < 3; j++) {
        bool line = true;
        for (int i = 0; i < 3; i++) {
            if (g[i][j] != 'X') {
                line = false;
                break;
            }
        }
        if (line) {
            return true;
        }
    }

    if (g[1][1] == 'X' && g[0][0] == 'X' && g[2][2] == 'X') {
        return true;
    }
    if (g[1][1] == 'X' && g[0][2] == 'X' && g[2][0] == 'X') {
        return true;
    }

    return false;
}

void chg(std::array<int, 2> p, char c) {
    g[p[0]][p[1]] = c;
}

bool solve()
{
    int cnt = 0;
    std::vector<std::array<int, 2>> pos;
    for (int i = 0; i < 3; i++) {
        std::cin >> g[i];
        for (int j = 0; j < 3; j++) {
            if (g[i][j] == 'X') {
                cnt++;
            }
            else if (g[i][j] == 'G') {
                pos.push_back({ i, j });
            }
        }
    }

    if (cnt <= 2) {
        return true;
    }
    else if (cnt == 4) {
        chg(pos[0], 'X');
        return chk();
    }
    else {
        for (int i = 0; i < 3; i++) {
            chg(pos[i], 'X'), chg(pos[(i + 1) % 3], 'X');
            if (chk()) {
                return true;
            }
            chg(pos[i], 'G'), chg(pos[(i + 1) % 3], 'G');
        }
    }

    return false;
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

    sp();

    return 0;
}