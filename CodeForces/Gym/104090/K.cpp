#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 5e5, LEN = 1e6;
struct Node {
    int nxt;
    int cnt;
    int ed;
}trie[LEN][26];
int tot;
i64 cnt[26][26], pre;
void insert(std::string &s) {
    int cur = 0, _cur = -1;
    for (int i = 0; i < s.size(); i++) {
        int to = s[i] - 'a';
        for (int j = 0; j < 26; j++) {
            cnt[j][to] += trie[cur][j].cnt;
        }

        if (trie[cur][to].nxt == 0) {
            trie[cur][to].nxt = ++tot;
        }
        trie[cur][to].cnt++;
        _cur = cur;
        cur = trie[cur][to].nxt;
    }
    trie[_cur][s.back() - 'a'].ed++;
    pre += (trie[_cur][s.back() - 'a'].cnt - trie[_cur][s.back() - 'a'].ed);
}

void solve()
{
    int n = 0, q = 0;
    std::cin >> n >> q;
    while(n--) {
        std::string s;
        std::cin >> s;
        insert(s);
    }

    while (q--) {
        std::string s;
        std::cin >> s;
        i64 ans = 0;
        for (int i = 0; i < 26; i++) {
            for (int j = i + 1; j < 26; j++) {
                ans += cnt[s[j] - 'a'][s[i] - 'a'];
            }
        }
        std::cout << ans + pre << '\n';
    }
}

int main()
{
    // IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}