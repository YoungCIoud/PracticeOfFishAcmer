// 终于抄完了
#include<bits/stdc++.h>
//using namespace std;
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string
#define please return
#define AC 0
using i64 = long long;
constexpr i64 Mod = 998244353, Inf = 1e9;

namespace Dinic
{
	constexpr int N = 11111, M = 233333;
	constexpr int S = 10100, T = 10101; // 源点 汇点
	
	struct Edge
	{
		int nex, to;
		i64 f;
	}edge[M * 2 + 5];
	int head[N + 5];
	int tot = 2;
	void add(int u, int v, i64 w)
	{
		edge[tot] = { head[u], v, w };
		head[u] = tot++;

		edge[tot] = { head[v], u, 0 };
		head[v] = tot++;
	}
	int level[N + 5];
	// bfs 建分层图
	bool mklv()
	{
		//puts("lvin");
		std::queue<int> q;
		memset(level, 0, sizeof level);
		q.push(S);
		level[S] = 1;
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
		//puts("dfsin");
		if (cur == T)
			return flow;

		i64 sum = 0;
		for (int e = head[cur]; e; e = edge[e].nex)
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
		//puts("dinicin");
		i64 res = 0;
		while (mklv())
			res += dfs(S, Inf);
		return res;
	}
}

int main()
{
	IOS;
	int n, m, k;
	std::cin >> n >> m >> k;
	vct<int> in(n + 5), out(n + 5);

	auto hs = [&](int x, int y, int z)
		{
			return ((x - 1) * k + (y - 1)) * 2 + z + 1;
		};
	
	// 建边
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= k; j++)
		{
			Dinic::add(hs(i, j, 0), hs(i, j, 1), 1);
			if (j < k)
				Dinic::add(hs(i, j, 0), hs(i, j + 1, 1), Inf);
		}
	}
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		std::cin >> u >> v;
		out[u]++, in[v]++;
		for (int j = 1; j <= k; j++)
			Dinic::add(hs(u, j, 1), hs(v, j, 0), Inf);
	}
	for (int i = 1; i <= n; i++)
	{
		if (in[i] == 0)
			Dinic::add(Dinic::S, hs(i, 1, 1), Inf);
		if (out[i] == 0)
			for (int j = 1; j <= k; j++)
				Dinic::add(hs(i, j, 0), Dinic::T, Inf);
	}

	i64 maxflow = Dinic::dinic();

	if (maxflow >= Inf)
	{
		std::cout << -1 << '\n';
		return 0;
	}

	// find min-cut
	vct<bool> cut(n + 5, false);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= k; j++)
		{
			int u = hs(i, j, 0), v = hs(i, j, 1);
			for (int e = Dinic::head[u]; e; e = Dinic::edge[e].nex)
			{
				if (Dinic::edge[e].to != v)
					continue;

				if (Dinic::level[u] and Dinic::level[v] == 0)
					cut[i] = true;
			}
		}
	}

	int cnt = 0;
	for (int i = 1; i <= n; i++)
		if (cut[i])
			cnt++;
	std::cout << cnt << '\n';
	for (int i = 1; i <= n; i++)
		if (cut[i])
			std::cout << i << ' ';
	
	please AC;
}
