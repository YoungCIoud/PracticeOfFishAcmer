// 终于不T了 QAQ
#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define aryi2 std::array<int, 2>
#define str std::string
using i64 = long long;
using u64 = unsigned long long;
namespace KMP
{
    vct<int> pi;
    // 获取s的前缀数组
    void init(std::string s)
    {
        pi.clear();
        int len = s.length();
        pi.assign(len, 0);
        for (int i = 1; i < len; i++)
        {
            int j = pi[i - 1];
            while (j && s[i] != s[j])
                j = pi[j - 1];
            if (s[i] == s[j])
                j++;
            pi[i] = j;
        }
        return;
    }
    // 返回text中第一个pattern的下标
    int find_first(std::string pattern, std::string text)
    {
        for (int i = 0, j = 0; i < text.length(); i++)
        {
            while (j && text[i] != pattern[j])
                j = pi[j - 1];
            if (text[i] == pattern[j])
                j++;
            if (j == pattern.length())
                return i - j + 1;
        }
        return -1;
    }
};

constexpr int MaxT = 2e6, N = 1e5, MaxS = 2e5;
int mp[N + 5];
namespace AC
{
    struct Node
    {
        int nex[26] = {};
        int fail = 0;

        bool vis = false;
    }node[MaxS + 5];
    int root = 0, tot = 1;

    void init()
    {
        for (int i = 0; i < tot; i++)
        {
            node[i].fail = node[i].vis = 0;
            memset(node[i].nex, 0, sizeof node[i].nex);
        }
        tot = 1;
    }

    void insert(str s, int idx)
    {
        int cur = root;
        for (auto c : s)
        {
            if (node[cur].nex[c - 'a'] == 0)
                node[cur].nex[c - 'a'] = tot++;
            cur = node[cur].nex[c - 'a'];
        }
        mp[idx] = cur;
    }

    void build()
    {
        std::queue<int> q;
        for (int i = 0; i < 26; i++)
            if (node[root].nex[i])
                q.push(node[root].nex[i]);

        while (!q.empty())
        {
            int cur = q.front();
            q.pop();

            for (int i = 0; i < 26; i++)
            {
                if (node[cur].nex[i])
                {
                    node[node[cur].nex[i]].fail = node[node[cur].fail].nex[i];
                    q.push(node[cur].nex[i]);
                }
                else
                {
                    node[cur].nex[i] = node[node[cur].fail].nex[i];
                }
            }
        }
        return;
    }

    void quiry(str s)
    {
        int cur = root;
        for (auto c : s)
        {
            cur = node[cur].nex[c - 'a'];
            for (int i = cur; i && node[i].vis == false; i = node[i].fail)
                node[i].vis = true;
        }
        return;
    }
};

void solve()
{
    int n;
    str A, C;
    std::cin >> n >> A >> C;

    KMP::init(C);
    AC::init();
    for (int i = 1; i <= n; i++)
        mp[i] = 0;

    for (int i = 1; i <= n; i++)
    {
        str b, bb;
        std::cin >> b >> bb;

        if (KMP::find_first(C, bb) != -1)
            AC::insert(b, i);
    }
    AC::build();
    AC::quiry(A);
    for (int i = 1; i <= n; i++)
        if (mp[i] && AC::node[mp[i]].vis)
            std::cout << i << ' ';
    std::cout << '\n';
}

int main()
{
    IOS;
    int t = 1;
    std::cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
