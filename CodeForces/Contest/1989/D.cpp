#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 1e6, Inf = 1e18, Mod = 998244353;
int a[N + 5], mn[N + 5], res[N + 5];
void solve()
{
	int n, m; 
	cin >> n >> m;
	int mx = 0;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		mx = max(mx, a[i]);
	}
	for (int i = 0; i <= mx; i++)
	{
		mn[i] = Inf;
	}

	for (int i = 1; i <= n; i++)
	{
		int t;
		cin >> t;
		mn[a[i]] = min(mn[a[i]], a[i] - t);
	}
	for (int i = 1; i <= mx; i++)
		mn[i] = min(mn[i], mn[i - 1]);
	for (int i = 1; i <= mx; i++)
		if (i >= mn[i])
			res[i] = 2 + res[i - mn[i]];
	
	int ans = 0;
	for (int i = 1; i <= m; i++)
	{
		int c;
		cin >> c;
		if (c > mx)
		{
			int tim = (c - mx) / mn[mx] + 1;
			ans += tim * 2;
			c -= tim * mn[mx];
		}
		ans += res[c];
	}
	cout << ans;
}

signed main()
{
	IOS;
	int t = 1;
	//cin >> t;
	while (t--)
	{
		solve();
	}
}
