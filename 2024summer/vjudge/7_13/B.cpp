#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 1e2, M = 1e5, Inf = 1e16, Mod = 1e9 + 7;
// 匈牙利算法找二分图最大匹配
int n;
vector<array<int, 2>> r(N + 5), b(N + 5);

bool mp[N + 5][N + 5], vis[N + 5];
int p[N + 5];
bool match(int cur)
{
	for (int i = 1; i <= n; i++)
	{
		if (!mp[cur][i] || vis[i]) continue;
		
		vis[i] = true;
		if (p[i] == 0 || match(p[i]))
		{
			p[i] = cur;
			return true;
		}
	}
	return false;
}

signed main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		int x, y;
		cin >> x >> y;
		r[i] = { x, y };
	}
	for (int i = 1; i <= n; i++)
	{
		int x, y;
		cin >> x >> y;
		b[i] = { x, y };
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			mp[i][j] = (r[i][0] < b[j][0] && r[i][1] < b[j][1]);

	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		fill(vis + 1, vis + 1 + n, false);
		if (match(i)) ans++;
	}
	cout << ans << endl;
}
