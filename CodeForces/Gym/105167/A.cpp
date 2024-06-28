#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
// using ll = long long;
const int N = 1e5, Inf = (1ll << 31) - 1, Mod = 998244353;
vector<int> g[N + 5], dep(N + 5), P(N + 5);
vector<vector<int>> fa(N + 5, vector<int>(20));

void dfs1(int cur, int fat, int depth)
{
	dep[cur] = depth;
	
	for (int to : g[cur])
	{
		if (to == fat) continue;
		// cout << to << " " << cur << endl;
		fa[to][0] = cur;
		dfs1(to, cur, depth + 1);
	}
}

void dfs2(int cur, int fa)
{
	for (int to : g[cur])
	{
		if (to == fa) continue;

		P[to] = P[cur] * (g[cur].size() - 1) % Mod;
		dfs2(to, cur);
	}
}

int qpow(int a, int p)
{
	int res = 1;
	for (; p; a = a * a % Mod, p >>= 1)
	{
		if (p & 1)
		{
			res = res * a % Mod;
		}
	}
	return res;
}

int inv(int a)
{
	return qpow(a, Mod - 2);
}

// u是起点，v是终点
int quiry(int u, int v)
{
	// 跳到同一高度
	if (dep[u] != dep[v])
	{
		if (dep[u] < dep[v])
		{
			swap(u, v);
		}
		for (int i = 20; ~i; i--)
		{
			if (dep[u] - (1ll << i) < dep[v]) continue;
			u = fa[u][i];
		}
	}
	if (u == v)
	{
		return u;
	}
	// cout << dep[u] << " " << dep[v] << endl;
	for (int i = 20; ~i; i--)
	{
		if (dep[u] < (1ll << i) || fa[u][i] == fa[v][i]) continue;
		u = fa[u][i], v = fa[v][i]; 
	}
	return fa[u][0];
}

signed main()
{
	int n, q;
	cin >> n >> q;
	for (int i = 1; i < n; i++)
	{
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs1(1, 0, 0);
	for (int i = 1; i < 20; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if ((1ll << i) > dep[j]) continue;
			fa[j][i] = fa[fa[j][i - 1]][i - 1];
		}
	}
	//for (int i = 1; i <= n; i++)
	//{
	//	for (int j = 0; j < 3; j++)
	//	{
	//		cout << fa[i][j] << " \n"[j == 2];
	//	}
	//}
	P[1] = 1;
	for (int to : g[1])
	{
		P[to] = g[1].size();
		dfs2(to, 1);
	}
	//for (int i = 1; i <= n; i++)
	//{
	//	cout << P[i] << " \n"[i == n];
	//}
	while (q--)
	{
		int a, b;
		cin >> a >> b;
		int c = quiry(a, b);
		int pa = P[a], pb = P[b], pc = P[c];
		int ans = 0;
		if (c == a)
		{
			ans = pb * inv(pa) % Mod;
			if (a != 1)
			{
				ans = ans * inv(g[a].size() - 1) % Mod * g[a].size() % Mod;
			}
		}
		else if (c == b)
		{
			ans = pa * inv(pb) % Mod * g[a].size() % Mod;
			ans = ans * inv(b == 1 ? g[b].size() : (g[b].size() - 1)) % Mod;
		}
		else
		{
			ans = pa * pb % Mod * inv(qpow(pc, 2)) % Mod;
			ans = ans * g[a].size() % Mod;
			if (c == 1)
			{
				ans = ans * inv(qpow(g[c].size(), 2)) % Mod * (g[c].size() - 1) % Mod;
			}
			else
			{
				ans = ans * inv(g[c].size() - 1) % Mod;
			}
		}
		//cout << tem * (pc * pc % Mod) % Mod * inv(pa) % Mod * inv(pb) % Mod << endl;
		//ans = ans * inv(qpow(pc, 2)) % Mod;
		//ans = ans * g[a].size() * ((c == a || c == b) ? 1 : (g[c].size() - 1)) % Mod;
		cout << ans << endl;
	}
	return 0;
}
