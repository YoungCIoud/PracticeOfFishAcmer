#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;


constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

ary<str, 2> brk(str s)
{
    int cnt = 0, p = 0;
    while (s[p] != ' ') p++;
    return { s.substr(0, p), s.substr(p + 1, s.size() - p - 2) };
}

std::map<str, str> mp;

void store(str type, str name)
{
    mp[name] = type;
}

void get(str name)
{
    if (mp.count(name))
    {
        std::cout << mp[name] << "\n";
    }
    else
    {
        // 指向名字
        int p = 0;
        while (name[p] != '.') p++;
        str type = mp[name.substr(0, p)];

        // 指向类型
        int q = 0;
        while(p < name.size() && q < type.size())
        {
            // 指向pair的first
            q += 5;
            if (name[p + 1] == 'f')
            {
                p += 6;
                continue;
            }
            
            int cnt = 0;
            while (cnt || type[q] != ',')
            {
                if (type[q] == '<') cnt++;
                if (type[q] == '>') cnt--;
                q++;
            }
            q += 1, p += 7;
        }
        int to = q, cnt = 0;
        while (cnt > 0 || (type[to] != ',' && type[to] != '>'))
        {
            if (type[to] == '<') cnt++;
            if (type[to] == '>') cnt--;
            to++;
        }
        std::cout << type.substr(q, to - q) << '\n';
    }
}

void solve()
{
    int n = 0, q = 0;
    std::cin >> n >> q;
    getchar();
    while (n--)
    {
        str s{};
        getline(std::cin, s);

        auto [type, name] = brk(s);

        store(type, name);
    }
    
    while (q--)
    {
        str s{};
        std::cin >> s;
        get(s);
    }

    return;
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