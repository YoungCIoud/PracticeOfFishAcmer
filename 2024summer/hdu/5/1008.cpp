// 虽然不知道为什么,他就是过了
#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string
#define get return
#define AC 0
using i64 = long long;
constexpr i64 Mod = 1e9 + 7, Inf = 1e18;
namespace Dinic
{
	// 以下数据依据具体要求确定
	constexpr int N = 3100, M = 100000; // 数据规模
	constexpr int S = 3001, T = 3002; // 源点 汇点

	// 链式前向星
	struct Edge
	{
		int nex, to;
		i64 f;
	}edge[M * 2 + 5]; // 因为要反向建边所以要开两倍空间
	int head[N + 5];
	int tot = 2;

	int ind[N + 5]; // 弧优化

	void init()
	{
		for (int i = 1; head[i]; i++)
			head[i] = 0;
		tot = 2;
		head[S] = head[T] = 0;
	}

	// 建边时正向边和反向边挨着建
	void add(int u, int v, i64 w)
	{
		//std::cout << u << " " << v << " " << w << '\n';
		edge[tot] = { head[u], v, w };
		head[u] = tot++;

		edge[tot] = { head[v], u, 0 };
		head[v] = tot++;
	}
	// bfs 建分层图
	// 同时可以根据level来找割边集
	int level[N + 5];
	bool mklv()
	{
		std::queue<int> q;
		memset(level, 0, sizeof level);
		q.push(S);
		level[S] = 1;
		ind[S] = head[S];
		while (not q.empty())
		{
			int cur = q.front();
			q.pop();

			for (int e = head[cur]; e; e = edge[e].nex)
			{
				auto& [nex, to, f] = edge[e];
				if (level[to] == 0 and f)
				{
					level[to] = level[cur] + 1;
					ind[to] = head[to];
					q.push(to);
				}
			}
			// return true when reach T
			if (level[T])
				return true;
		}
		// cannot reach T
		return false;
	}

	i64 dfs(int cur, i64 flow)
	{
		if (cur == T)
			return flow;

		i64 sum = 0;
		// 注意弧优化
		for (int e = ind[cur]; e; ind[cur] = e, e = edge[e].nex)
		{
			auto& [nex, to, f] = edge[e];
			if (f <= 0 or level[to] != level[cur] + 1)
				continue;

			// 总共流入了flow, 能够从这条边流出的最大值
			i64 mx = dfs(to, std::min(flow - sum, f));
			f -= mx;
			edge[e ^ 1].f += mx;
			sum += mx;

			if (sum == flow)
				return flow;
		}
		if (sum == 0)
			level[cur] = 0;
		return sum;
	}

	i64 dinic()
	{
		i64 res = 0;
		while (mklv())
			res += dfs(S, Inf);
		return res;
	}
}
void solve()
{
	Dinic::init();

	int n, k;
	std::cin >> n >> k;
	vct<int> a(k), val(k);
	std::map<int, int> hs;
	int cnt = 1;
	vct<bool> yes(n + 1, false);
	for (auto& i : a)
	{
		std::cin >> i;
		yes[i] = true;
		hs[i] = cnt++;
	}
	
	int ans = 0;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < n - 1; j++)
		{
			int u, v, w;
			std::cin >> u >> v >> w;
			if (!yes[u] || !yes[v]) continue;

			if (!i)
			{
				ans += w;
				val[hs[u] - 1] += w;
				val[hs[v] - 1] += w;
			}

			ans += w;
			Dinic::add(Dinic::S, cnt, w);
			Dinic::add(cnt, hs[u], Inf);
			Dinic::add(cnt, hs[v], Inf);
			cnt++;
		}
	}
	for (auto& i : a)
		Dinic::add(hs[i], Dinic::T, val[hs[i] - 1]);

	std::cout << ans - Dinic::dinic() << '\n';
	return;
}

int main()
{
	IOS;
	int t = 1;
	std::cin >> t;
	while (t--)
		solve();

	get AC;
}
