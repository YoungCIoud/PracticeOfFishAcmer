#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 2e5, Inf = 1e18, Mod = 998244353;
int a[N + 5], b[N + 5];
void solve()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	int cnt[2] = { 0, 0 }, sum[2] = { 0, 0 };
	for (int i = 1; i <= n; i++)
	{
		cin >> b[i];
		if (a[i] == b[i])
		{
			if (a[i])
			{
				cnt[(a[i] >> 1) & 1]++;
			}
		}
		else
		{
			if (a[i] == 1) sum[0]++;
			if (b[i] == 1) sum[1]++;
		}
	}
	// cout << cnt[0] << " " << cnt[1] << endl;
	if (sum[0] > sum[1]) swap(sum[0], sum[1]);

	if (sum[1] - sum[0] <= cnt[0])
	{
		cnt[0] -= (sum[1] - sum[0]);
		sum[0] = sum[1] + cnt[0] / 2;
		sum[1] += (cnt[0] + 1) / 2;
	}
	else
	{
		sum[0] += cnt[0];
	}

	if (sum[1] - sum[0] <= cnt[1])
	{
		cnt[1] -= (sum[1] - sum[0]);
		sum[1] = sum[0] - cnt[1] / 2;
		sum[0] -= (cnt[1] + 1) / 2;
	}
	else
	{
		sum[1] -= cnt[1];
	}
	cout << min(sum[0], sum[1]) << endl;
}

signed main()
{
	int t = 1;
	cin >> t;
	while (t--)
	{
		solve();
	}
}
