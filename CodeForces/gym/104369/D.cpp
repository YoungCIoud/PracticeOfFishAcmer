#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 1e6, Inf = 1e18, Mod = 998244353;
pair<int, int> pos[N + 5];

// 从 x 到 y
bool ok(pair<int, int> a, pair<int, int> b)
{
	return a.first <= b.first && a.second <= b.second;
}

void solve()
{
	int n, m; 
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			int a;
			cin >> a;
			if (a < m + n)
			{
				pos[a] = { i, j };
			}
		}
	}
	

	auto check = [&](int mid)->bool
		{
			vector<pair<int,int>> route(mid + 1);
			for (int i = 0; i <= mid; i++)
			{
				route[i] = pos[i];
			}
			sort(route.begin(), route.end(), [](pair<int, int> a, pair<int, int> b) {
				return a.first <= b.first && a.second <= b.second;
				});
			for (int i = 0; i < mid; i++)
				if (!ok(route[i], route[i + 1])) return false;
			return true;
		};
	int l = 0, r = m + n - 2;
	while (l <= r)
	{
		int m = l + r >> 1;
		if (check(m)) l = m + 1;
		else r = m - 1;
	}
	cout << l << endl;
}

signed main()
{
	IOS;
	int t;
	cin >> t;
	while (t--)
		solve();
	return 0;
}
