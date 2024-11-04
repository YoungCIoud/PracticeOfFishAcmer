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

constexpr i64 Mod = 998244353, Inf = 1e15;
constexpr int N = 1e5, M = 2e5;
int n, m;
std::vector<std::array<int, 2>> g[N + 5];
std::vector<i64> w(M + 5);
std::vector<bool> vis(M + 5);

std::vector<int> dfn(N + 5), low(N + 5), num(N + 5), e(M + 5);
int tim;
void dfs(int cur, int fa = 0) {
	tim++;
	dfn[cur] = tim;
	low[cur] = tim;
	int eid = M;
	for (auto &[to, id] : g[cur]) {
		if (to == fa) {
			eid = id;
			continue;
		}
		if (not vis[id]) {
			vis[id] = true;
			num[cur]++;
		}
		
		if (dfn[to]) {
			low[cur] = std::min(low[cur], dfn[to]);
		}
		else {
			dfs(to, cur);
			num[cur] += num[to];
			low[cur] = std::min(low[cur], low[to]);
		}
	}
	
	if (dfn[cur] <= low[cur]) {
		// 当前节点跟父亲节点的连边是一条割边 
		e[eid] = num[cur];
	}
	return;
}

int main() {
	std::cin >> n >> m;
	i64 ans = 0;
	for (int i = 0; i < m; i++) {
		int u = 0, v = 0;
		std::cin >> u >> v >> w[i];
		ans += w[i];
		g[u].push_back({ v, i });
		g[v].push_back({ u, i });
	}
	
	i64 mn = 0;
	if (m & 1) {
		dfs(1);
		mn = Inf;
		for (int i = 0; i < m; i++) {
			// e[i] 把第i条边忽略掉后形成的两个块中其中一块边的数量 
			if (e[i] % 2 == 0) {
				mn = std::min(mn, w[i]);
			}
		}
	}
	
	std::cout << ans - mn << '\n';
	return 0;
}