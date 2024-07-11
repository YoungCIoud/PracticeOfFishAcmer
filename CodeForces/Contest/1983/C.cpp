#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 2e5, Inf = 1e18, Mod = 998244353;
int n, tot;
int pre[3][N + 5];

bool vis[3], flag;
int ord[3], ans[6];
void dfs(int dep)
{
	if (flag) return;
	if (dep >= 3)
	{
		flag = true;
		int l = 0, r = 0;
		for (int i = 0; i < 3 && flag; i++)
		{
			l = r + 1;
			if (l > n)
			{
				flag = false;
				break;
			}
			r = lower_bound(pre[ord[i]] + 1, pre[ord[i]] + 1 + n, tot + pre[ord[i]][r]) - pre[ord[i]];
			if (r > n)
			{
				flag = false;
			}

			ans[ord[i] * 2] = l;
			ans[ord[i] * 2 + 1] = r;
		}
		return;
	}
	for (int i = 0; i < 3; i++)
	{
		if (vis[i]) continue;
		
		ord[dep] = i;
		vis[i] = true;
		dfs(dep + 1);
		vis[i] = false;
	}
}

void solve()
{
	tot = 0;
	cin >> n;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			int v;
			cin >> v;
			pre[i][j] = pre[i][j - 1] + v;
			tot += v;
		}
	}
	tot /= 3;
	tot = (tot + 2) / 3;

	flag = false;
	fill(vis, vis + 3, false);
	dfs(0);

	if (flag)
	{
		for (int i = 0; i < 6; i++)
		{
			cout << ans[i] << " \n"[i == 5];
		}
	}
	else cout << -1 << endl;

	return;
}

signed main()
{
	int t;
	cin >> t;
	while (t--)
	{
		solve();
	}
	return 0;
}
