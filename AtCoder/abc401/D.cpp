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

constexpr i64 Mod = 1e9;
constexpr int N = 2e5;

void solve() {
    int n = 0, k = 0;
    std::string s;
    std::cin >> n >> k >> s;
    s = "." + s + ".";
    
    for (int i = 1; i <= n; i++) {
        if (s[i] == '?' && (s[i - 1] == 'o' || s[i + 1] == 'o')) {
            s[i] = '.';
        }
        else if (s[i] == 'o') {
            k--;
        }
    }

    if (k == 0) {
        for (int i = 1; i <= n; i++) {
            if (s[i] == '?') {
                s[i] = '.';
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (s[i] != '?') {
            continue;
        }

        int j = i;
        while (s[j] == '?') {
            j++;
        }
        k -= (j - i + 1 >> 1);
        i = j;
    }

    if (k == 0) {
        for (int i = 1; i <= n; i++) {
            if (s[i] != '?') {
                continue;
            }

            int j = i;
            while (s[j] == '?') {
                j++;
            }
            int len = j - i;
            if (len & 1) {
                for (int l = 0; l < len; l++) {
                    s[i + l] = "o."[l & 1];
                }
            }
            i = j;
        }
    }
    std::cout << s.substr(1, n) << '\n';
    return;
}

int main () {
    IOS;
    int _t = 1;
    //std::cin >> _t;
    
    while (_t--) {
        solve();
    }

    return 0;
}
