// 我到底怎样才能想到这样的正解
#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string
#define get return
#define AC 0
using i64 = long long;
using u64 = unsigned int long long;
constexpr i64 Mod = 1e9 + 7, Inf = 1e18;
constexpr int N = 2e5;
std::unordered_map<int, int> hs;
int cnt;

// 维护区间最大值和最大值的个数
typedef ary<int, 2> Node;
Node tr[4 * N + 5];
int tag[4 * N + 5];
Node operator+ (const Node & x, const Node & y)
{
	if (x[0] == y[0])
		return Node{ x[0], x[1] + y[1] };
	else
		return x[0] > y[0] ? x : y;
}

void push_up(int cur)
{
	tr[cur] = tr[cur << 1] + tr[cur << 1 | 1];
}

void push_down(int cur)
{
	tr[cur << 1][0] += tag[cur];
	tag[cur << 1] += tag[cur];
	tr[cur << 1 | 1][0] += tag[cur];
	tag[cur << 1 | 1] += tag[cur];

	tag[cur] = 0;
}

void build(int cur, int l, int r)
{
	tag[cur] = 0;

	if (l == r)
		return void(tr[cur] = { 0, 1 });

	int m = l + r >> 1;
	build(cur << 1, l, m);
	build(cur << 1 | 1, m + 1, r);

	push_up(cur);
}

void upd(int cur, int l, int r, int sl, int sr, int val)
{
	if (sl <= l && r <= sr)
	{
		tr[cur][0] += val;
		if (l != r)
			tag[cur] += val;
		return;
	}

	if (tag[cur])
		push_down(cur);

	int m = l + r >> 1;
	if (sl <= m)
		upd(cur << 1, l, m, sl, sr, val);
	if (sr > m)
		upd(cur << 1 | 1, m + 1, r, sl, sr, val);

	push_up(cur);
}

Node quiry(int cur, int l, int r, int sl, int sr)
{
	if (sl <= l && r <= sr)
		return tr[cur];

	if (tag[cur])
		push_down(cur);

	int m = l + r >> 1;
	if (sr <= m)
		return quiry(cur << 1, l, m, sl, sr);
	else if (sl > m)
		return quiry(cur << 1 | 1, m + 1, r, sl, sr);
	else
		return (quiry(cur << 1, l, m, sl, sr) + quiry(cur << 1 | 1, m + 1, r, sl, sr));
}

void solve()
{
	hs.clear();
	cnt = 1;

	int n, k;
	std::cin >> n >> k;

	vct<int> a(n + 1);
	for (int i = 1; i <= n; i++)
	{
		std::cin >> a[i];
		if (!hs[a[i]])
			hs[a[i]] = cnt++;
		a[i] = hs[a[i]];
	}
	

	// 预处理las, nex
	vct<int> pos(cnt, 0);
	vct<int> las(n + 1, 0), nex(n + 1, 0);
	for (int i = 1; i <= n; i++)
	{
		if (pos[a[i]])
			nex[pos[a[i]]] = i;

		las[i] = pos[a[i]], pos[a[i]] = i;
	}

	// solve
	build(1, 1, n);
	vct<ary<int, 2>> rng(cnt);
	vct<int> num(cnt, 0); // 记录当前每个数的数量
	int tot = 0; // 当前已出现的不同数的数量
	i64 ans = 0;
	for (int i = n; i; i--)
	{
		if (num[a[i]] == 0)
			tot++;
		auto& [l, r] = rng[a[i]];
		if (num[a[i]] == k)
		{
			upd(1, 1, n, l, r - 1, -1);

			r = l;
			l = las[l];
		}
		else if (++num[a[i]] == k)
			l = pos[a[i]], r = n + 1;

		if (nex[i] - 1 >= 1)
			upd(1, 1, n, 1, nex[i] - 1, -1);
		if (i - 1 >= 1)
			upd(1, 1, n, 1, i - 1, 1);

		if (l)
		{
			upd(1, 1, n, l, r - 1, 1);
			auto res = quiry(1, 1, n, l, r - 1);
			if (res[0] == tot)
				ans += 1ll * res[1];
		}
	}
	std::cout << ans << '\n';
}

int main()
{
	int t = 1;
	std::cin >> t;
	while (t--)
		solve();
	return 0;
}
