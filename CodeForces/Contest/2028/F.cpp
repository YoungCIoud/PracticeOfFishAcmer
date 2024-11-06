#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
    #define cout cout << ">>>\t"
#else
    #define debug(...)
    #define sp()
    #define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 2e5, M = 1e4, L = 14, Inf = 1e9;
std::deque<std::pair<int, std::bitset<M + 1>>> q; // 非 0 非 1
std::bitset<M + 1> all; // 记录当前为止所有出现过的数
std::bitset<M + 1> cur; // 当前状态
std::bitset<M + 1> lst; // 上一个的状态
std::bitset<M + 1> zero; // 开头到目前为止最后一个0的状态
void init() {
    q.clear();
    all = 1;
    lst = 1;
    zero = 0;
}

void solve()
{
    init();
    int n = 0, m = 0;
    std::cin >> n >> m;
    while (n--) {
        int a = 0;
        std::cin >> a;

        if (a == 0) {
            cur = zero = all;
            q.clear();
        }
        else if (a == 1) {
            cur = lst | (lst << 1);
        }
        else {
            cur = zero;
            q.push_front({ a, lst });
            for (int i = 0, prd = q[i].first; prd <= m; prd *= q[++i].first) {
                cur |= (q[i].second << prd);
                if (i == q.size() - 1) {
                    break;
                }
            }
            while (q.size() >= L) {
                q.pop_back();
            }
        }
        
        lst = cur;
        all |= cur;
    }
    std::cout << (cur[m] ? "Yes" : "No") << '\n';
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

    sp();

    return 0;
}