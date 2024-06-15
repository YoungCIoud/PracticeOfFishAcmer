#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 1e6, Inf = 1e18, Mod = 998244353;
pair<int, int> a[N + 5];

void solve()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i].first >> a[i].second;
	}
	sort(a, a + n);
	int l = 0, r = n - 1;
	int ans = 0, have = 0;
	while (l < r)
	{
		have = a[l].second;
		for (; l < r && have > 0; r--)
		{
			if (a[r].second <= have)
			{
				ans += (a[r].first - a[l].first) * a[r].second;
				have -= a[r].second;
			}
			else
			{
				ans += (a[r].first - a[l].first) * have;
				a[r].second -= have;
				break;
			}
		}
		
		l++;
	}
	cout << ans << endl;
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
