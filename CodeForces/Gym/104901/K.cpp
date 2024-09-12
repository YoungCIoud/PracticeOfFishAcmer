#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 5e5, M = 1e9, Inf = M + M;

class mset
{
public:
    void init()
    {
        less.clear(), greater.clear();
        less.insert(-Inf), greater.insert(Inf);
        less_sum = 0, greater_sum = 0;
    }
    void insert(int val)
    {
        if (val < *greater.begin()) less.insert(val), less_sum += val;
        else greater.insert(val), greater_sum += val;

        adjust(); 
    }
    void erase(int val)
    {
        if (val < *greater.begin()) less.erase(less.lower_bound(val)), less_sum -= val;
        else greater.erase(greater.lower_bound(val)), greater_sum -= val;

        adjust();
    }
    bool chk(i64 k)
    {
        int m = 0;
        int d = less.size() - greater.size();

        if (d)
            m = *less.begin();
        else
            m = *less.begin() + *greater.begin() >> 1;
        
        return (greater_sum - less_sum + d * m <= k); 
    }
private:
    std::multiset<int, std::greater<int>> less;
    std::multiset<int> greater;
    i64 less_sum, greater_sum;

    void adjust()
    {
        while (greater.size() > less.size())
        {
            auto it = greater.begin();
            less.insert(*it);
            less_sum += *it;

            greater_sum -= *it;
            greater.erase(it);
        }
        while (less.size() > greater.size() + 1)
        {
            auto it = less.begin();
            greater.insert(*it);
            greater_sum += *it;

            less_sum -= *it;
            less.erase(less.begin());
        }
    }
}S;


void solve()
{
    S.init();

    int n = 0;
    i64 k = 0;
    std::cin >> n >> k;

    vct<int> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        std::cin >> a[i];
        a[i] -= i;
        a[i] += n;
    }

    int ans = 0;
    // 左闭右开
    for (int l = 1, r = 1; l <= n; S.erase(a[l]), l++)
    {
        while (S.chk(k))
        {
            ans = std::max(ans, r - l);
            if (r <= n) S.insert(a[r++]);
            else break;
        }
    }
    std::cout << ans << '\n';
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

    system("pause");

    return 0;
}