// 根据不同的数据范围选算法
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
const int N = 1e5, M = 1ll << 32, Inf = 1e16, Mod = 1e9 + 7;
int m;
map<int, int> mp[N + 5];
vector<array<int, 3>> edge(N + 5);
int fa[N + 5];
bool now[N + 5];
int getfa(int u)
{
	return fa[u] == u ? u : (fa[u] = getfa(fa[u]));
}
bool merge(int u, int v)
{
	int fu = getfa(u), fv = getfa(v);
	fa[fu] = fv;
	return fu != fv;
}

int kruskal(int num, vector<int> &e)
{
	int ans = 0;
	for (auto idx : e)
	{
		auto [len, u, v] = edge[idx];
		if (merge(u, v))
			ans += len, num--;
	}
	return num == 1 ? ans : -1;
}

int solve()
{
	int n;
	cin >> n;
	vector<int> s(n), e;
	for (int& i : s)
	{
		cin >> i;
		fa[i] = i;
	}
	
	if (n <= 300)
	{
		sort(s.begin(), s.end());
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
				if (mp[s[i]].count(s[j]))
					e.push_back(mp[s[i]][s[j]]);
		sort(e.begin(), e.end());
	}
	else
	{
		for (auto i : s) now[i] = true;
		for (int i = 1; i <= m; i++)
		{
			auto [len, u, v] = edge[i];
			if (now[u] && now[v])
				e.push_back(i);
		}
		for (auto i : s) now[i] = false;;
	}
	return kruskal(n, e);
}
signed main()
{
	IOS;
	int n, q;
	cin >> n >> m >> q;
	for (int i = 1; i <= m; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		if (a > b) swap(a, b);
		edge[i] = { c, a, b };
	}
	sort(edge.begin() + 1, edge.begin() + 1 + m, [](array<int, 3> x, array<int, 3> y) {
		return  x[0] < y[0];
		});
	for (int i = 1; i <= m; i++)
		mp[edge[i][1]][edge[i][2]] = i;

	while(q--)
		cout << solve() << endl;
	return 0;
}
