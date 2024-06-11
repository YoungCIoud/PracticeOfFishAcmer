#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 2e5, Inf = 1e18, Mod = 998244353;
int to[N + 5], dp[N + 5];
vector<int> g[N];

int dfn[N + 5], low[N + 5], tim, scc[N + 5], cnt[N + 5];
int stk[N + 5], top;
bool vis[N + 5];
void trajan(int cur)
{
	if (dfn[cur]) return;
	dfn[cur] = low[cur] = ++tim;
	stk[top++] = cur, vis[cur] = true;
	
	if (!dfn[to[cur]])
	{
		trajan(to[cur]);
		low[cur] = min(low[cur], low[to[cur]]);
	}
	else if (vis[to[cur]]) low[cur] = min(low[cur], low[to[cur]]);

	if (low[cur] == dfn[cur])
	{
		//cout << cur << endl;
		int t;
		while (t = stk[--top])
		{
			vis[t] = 0;
			scc[t] = cur;
			cnt[cur]++;
			if (cur == t) break;
		}
	}
}

signed main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> to[i];
	}

	for (int i = 1; i <= n; i++)
	{
		trajan(i);
	}

	int ans = n;
	for (int i = 1; i <= n; i++)
	{
		//if (cnt[i] == 1) cout << i << " ";
		if (cnt[i])
		{
			ans += cnt[i] * (cnt[i] - 1);
		}
	}
	//cout << endl;

	//cout << ans;
	auto dfs = [&](auto self, int cur)->int
		{
			if (dp[cur]) return dp[cur]; // 访问过的
			if (cnt[to[cur]] != 1) return (dp[cur] = cnt[scc[to[cur]]]); // 非自环的环
			if (to[cur] == cur) return 0; // 自环

			return (dp[cur] = 1 + self(self, to[cur]));
 		};
	for (int i = 1; i <= n; i++)
	{
		if (cnt[i] == 1 && to[i] != i)
		{
			//cout << i << endl;
			ans += dfs(dfs, i);
		}
	}

	cout << ans;
	return 0;
}
