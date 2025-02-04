#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 Mod = 1e9 + 7;
constexpr int N = 1e5, M = 1e5, L = 1e6, T = 100;

int tr[L + 5][27];
int tot = 0;

class BIT {
private:
    int n;
    std::vector<int> a;

    int lowbit(int x) {
        return x & -x;
    }

    int sum(int pos) {
        int res = 0;
        for (int i = pos; i > 0; i -= lowbit(i)) {
            res += a[i];
        }
        return res;
    }
public:
    BIT(int _n) {
        n = _n;
        a.assign(n + 1, 0);
    }

    void add(int pos, int val) {
        for (int i = pos; i <= n; i += lowbit(i)) {
            a[i] += val;
        }
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};

void insert(std::string s, int id, BIT &cnt) {
    int cur = 0;
    for (auto &c : s) {
        int to = c - 'a';
        if (tr[cur][to] == 0) {
            tr[cur][to] = ++tot;
        }
        else {
           cnt.add(tr[tr[cur][to]][26], -1);
        }
        cur = tr[cur][to];
        tr[cur][26] = id;
    }
    cnt.add(id, s.length());
}

int main () {
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector s(n + 1, std::string{});
    std::vector ans(m, 0);
    BIT cnt(n);
    for (int i = 1; i <= n; i++) {
        std::cin >> s[i];
    }
    std::vector q(n + 1, std::vector<std::array<int, 2>>{});
    for (int i = 0; i < m; i++) {
        int l = 0, r = 0;
        std::cin >> l >> r;
        q[r].push_back({ l, i });
    }

    std::pair<int, int> stk[n];
    int top = 0;
    for (int r = 1; r <= n; r++) {
        insert(s[r], r, cnt);
        int len = s[r].length();
        while (top && stk[top - 1].second <= len) {
            top--;
        }
        stk[top++] = { r, len };
        for (auto &[l, id] : q[r]) {
            ans[id] = (cnt.sum(l, r)) * 2 - (*std::lower_bound(stk, stk + top, std::make_pair(l, 0))).second;
        }
    }

    for (auto &i : ans) {
        std::cout << i << '\n';
    }

    return 0;
}

/*
in
3 3
nowcoder
nowdays
now
1 3
1 2
3 3
out
16
16
3

in
4 1
nowcoder
nowdays
days
coder
1 4
out
34
*/