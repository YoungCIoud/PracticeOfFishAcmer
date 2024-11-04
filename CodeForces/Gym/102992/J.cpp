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
using u32 = unsigned int;

constexpr i64 Mod = 998244353;
constexpr int N = 2e5, Q = 2e5;
constexpr u32 Inf = 1 << 30;
struct Node {
    u32 mn, cnt, se; // 最小值 最小值的个数 次小值
    u32 sum; // 异或和
    std::vector<u32> tot; // 某一位为 1 的数的个数
    u32 tag;
    Node(u32 num = Inf) {
        mn = num;
        cnt = 1;
        se = Inf;
        sum = num;
        tag = Inf;

        tot.assign(30, 0);
        for (int i = 0; i < 30; i++) {
            if (num >> i & 1) {
                tot[i] = 1;
            }
        }
    }

    Node operator+ (const Node &a) {
        Node tmp;
        if (mn == a.mn) {
            tmp.mn = mn;
            tmp.cnt = cnt + a.cnt;
            tmp.se = (se < a.se) ? se : a.se;
        }
        else if (a.mn < mn) {
            tmp.mn = a.mn;
            tmp.cnt = a.cnt;
            tmp.se = (mn < a.se) ? mn : a.se;
        }
        else {
            tmp.mn = mn;
            tmp.cnt = cnt;
            tmp.se = (se < a.mn) ? se : a.mn;
        }
        
        tmp.sum = a.sum ^ sum;
        for (int i = 0; i < 30; i++) {
            tmp.tot[i] = a.tot[i] + tot[i];
        }
        return tmp;
    }
} tr[N * 4];
u32 a[N + 5];

void push_up(int cur) {
    tr[cur] = tr[cur << 1] + tr[cur << 1 | 1];
}
void make_tag(int cur, int tg) {
    if (tg <= tr[cur].mn) {
        return;
    }
    auto &[mn, cnt, se, sum, tot, tag] = tr[cur];
    tag = tg;
    for (int i = 0; i < 30; i++) {
        if (mn >> i & 1) {
            tot[i] -= cnt;
        }
        if (tg >> i & 1) {
            tot[i] += cnt;
        }
    }

    if (cnt & 1) {
        sum ^= (mn ^ tg);
    }
    mn = tg;
    return;
}
void push_down(int cur) {
    if(tr[cur].tag == Inf) {
        return;
    }
    make_tag(cur << 1, tr[cur].tag);
    make_tag(cur << 1 | 1, tr[cur].tag);
    tr[cur].tag = Inf;
}
void build(int cur, int l, int r) {
    if (l == r) {
        tr[cur] = Node(a[l]);
        return;
    }
    int m = l + r >> 1;
    build (cur << 1, l, m);
    build (cur << 1 | 1, m + 1, r);
    push_up(cur);
}
void upd(int cur, int l, int r, int ls, int rs, u32 x) {
    // 区间最小值比x大，直接返回
    if (tr[cur].mn >= x) {
        return;
    }
    // x 属于 (mn, se)， 直接更新mn
    if (ls <= l && r <= rs && tr[cur].se > x) {
        make_tag(cur, x);
        return;
    }

    int m = l + r >> 1;
    push_down(cur);
    if (m >= ls) {
        upd(cur << 1, l, m, ls, rs, x);
    }
    if (m < rs) {
        upd(cur << 1 | 1, m + 1, r, ls, rs, x);
    }
    push_up(cur);
    return;

}
Node quiry(int cur, int l, int r, int ls, int rs) {
    if (ls <= l && r <= rs) {
        return tr[cur];
    }

    push_down(cur);
    int mid = l + r >> 1;
    if (rs <= mid) {
        return quiry(cur << 1, l, mid, ls, rs);
    }
    else if (mid < ls) {
        return quiry(cur << 1 | 1, mid + 1, r, ls, rs);
    }
    else {
        return quiry(cur << 1, l, mid, ls, rs) + quiry(cur << 1 | 1, mid + 1, r, ls, rs);
    }
}


void solve()
{
    int n = 0, q = 0;
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }

    build(1, 1, n);
    while (q--) {
        u32 ope = 0, l = 0, r = 0, x = 0;
        std::cin >> ope >> l >> r >> x;
        if (ope == 1) {
            upd(1, 1, n, l, r, x);
        }
        else {
            auto res = quiry(1, 1, n, l, r);
            res.sum ^= x;
            int p = -1;
            for (int i = 0; i < 30; i++) {
                if (res.sum >> i & 1) {
                    p = i;
                }
            }
            std::cout << (~p ? (res.tot[p] + (x >> p & 1)) : 0) << '\n';
        }
    }
}

int main()
{
    IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    sp();

    return 0;
}