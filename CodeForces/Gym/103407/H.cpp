#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;
std::vector<int> a(N + 5), t(N + 5);
std::vector<int> g[N + 5];
std::vector<i64> dp(N + 5), sum(N + 5);

void dfs(int cur, int fa) {
	i64 val = 0;
	bool flag = false;
	for (auto &to : g[cur]) {
		if (to == fa) {
			continue;
		}
		if (t[to] == 3) {
			flag = true;
		}

		dfs(to, cur);
		sum[cur] += dp[to];
		dp[cur] = std::max(dp[cur], 1ll * a[to]);
	}
	dp[cur] += sum[cur];
	
	if (not flag || g[cur].size() <= 2) {
		return;
	}

	int mx1 = 0, mx2 = 0;
	for (auto &to : g[cur]) {
		if (to == fa || t[to] != 3) {
			continue;
		}

		if (a[to] >= a[mx1]) {
			mx2 = mx1;
			mx1 = to;
		}
		else if (a[to] >= a[mx2]) {
			mx2 = to;
		}
	}

	for (auto &to : g[cur]) {
		if (to == fa) {
			continue;
		}

		i64 val = sum[cur] - dp[to] + a[to] + sum[to] + (to == mx1 ? a[mx2] : a[mx1]);
		dp[cur] = std::max(dp[cur], val);
	}
	
	return;
}

void solve()
{
	int n = 0;
	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		g[i].clear();
		dp[i] = 0;
		sum[i] = 0;
	}

	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
	}
	for (int i = 1; i <= n; i++) {
		std::cin >> t[i];
	}
	for (int i = 0; i < n - 1; i++) {
		int u = 0, v = 0;
		std::cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	g[1].push_back(0);

	dfs(1, 0);
	
	std::cout << dp[1] + 1ll * a[1] << '\n';
}

int main()
{
	// IOS;
	int _t = 1;
	std::cin >> _t;
	
	while (_t--)
	{
		solve();
	}

	system("pause");

	return 0;
}