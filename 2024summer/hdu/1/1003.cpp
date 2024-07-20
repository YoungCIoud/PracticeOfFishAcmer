// 事实证明 哥哥的内存池的做法是优的
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
using u64 = unsigned int long long;
const int N = 5e5, M = 1 << 20;
struct node
{
    node* l = nullptr;
    node* r = nullptr;
    u64 sum = 0;
    int cnt = 0;
}pool[21 << 19];
int tot;
u64 res = 0;
vector<int> g[N + 5];
vector<u64> sum(N + 5), pmx(N + 5), A(N + 5);
vector<node*> t(N + 5);
void add(node*& t, int l, int r, u64 val)
{
    if (t == nullptr)
        t = &pool[tot++];
    t->cnt++;
    t->sum += val * val;
    if (l == r)
        return;
    int m = l + r >> 1;
    if (val <= m)
        add(t->l, l, m, val);
    else
        add(t->r, m + 1, r, val);
}

node* merge(node* a, node* b, int l, int r, u64& ans)
{
    if (a == nullptr) return b;
    if (b == nullptr) return a;
    if (l == r)
    {
        ans += a->cnt * b->sum * 2;
        a->cnt += b->cnt;
        a->sum += b->sum;
        return a;
    }
    
    a->cnt += b->cnt;
    a->sum += b->sum;

    int m = l + r >> 1;
    if (a->l != nullptr && b->r != nullptr)
        ans += b->r->sum * a->l->cnt * 2;
    if (a->r != nullptr && b->l != nullptr)
        ans += a->r->sum * b->l->cnt * 2;
    a->l = merge(a->l, b->l, l, m, ans);
    a->r = merge(a->r, b->r, m + 1, r, ans);
    return a;
}

void dfs(int cur, int fa)
{
    sum[cur] = A[cur];
    pmx[cur] = A[cur] * A[cur];
    add(t[cur], 1, M, A[cur]);
    for (auto to : g[cur])
    {
        if (to == fa) continue;
        dfs(to, cur);
        sum[cur] += sum[to];
        pmx[cur] += pmx[to];
        t[cur] = merge(t[cur], t[to], 1, M, pmx[cur]);
    }
    //cout << cur << ":" << pmx[cur] << "," << sum[cur] << endl;
    res ^= pmx[cur] - sum[cur] * sum[cur];
}

int main()
{
    IOS;
    int n;
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> A[i];
    }
    dfs(1, 0);
    cout << res;
    return 0;
}