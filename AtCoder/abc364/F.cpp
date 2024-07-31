// 其实这题不算难
#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string
#define get return
#define AC 0
using i64 = long long;
constexpr int Mod = 998244353, Inf = 1e9, N = 2e5, M = 1e9;

// 并查集
int fa[N + 5];
int getfa(int u)
{
	return u == fa[u] ? u : (fa[u] = getfa(fa[u]));
}
// 将u合并到v上
void merge(int u, int v)
{
	if (u == 199999)
	{
		u = u;
	}
	fa[getfa(u)] = getfa(v);
}

int main()
{
	int n, q;
	std::cin >> n >> q;
	for (int i = 1; i <= n; i++)
		fa[i] = i;
	vct<ary<int, 3>> a(q);
	for (int i = 1; i <= q; i++)
	{
		int l, r, c;
		std::cin >> l >> r >> c;
		a[i - 1] = { l, r, c};
	}
	sort(a.begin(), a.end(), [](ary<int, 3> x, ary<int, 3> y) {
		return x[2] < y[2];
		});
	
	i64 ans = 0;
	for (auto& [l, r, c] : a)
	{
		int cnt = 1, cur = getfa(l);
		//std::cout << c << '\n';
		while (cur < r)
		{
			int nex = getfa(cur + 1);
			merge(cur, nex);
			cnt++;
			cur = nex;
		}
		ans += 1ll * c * cnt;
	}

	getfa(1);
	for (int i = 2; i <= n; i++)
		if (fa[1] != getfa(i))
		{
			ans = -1;
			break;
		}
	std::cout << ans << '\n';
	get AC;
}
