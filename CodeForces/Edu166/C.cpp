#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 2e5, A = 1e6, Inf = 1e18;

void solve()
{
	int n, m;
	cin >> n >> m;
	vector<int> a(n + m + 1 + 5), b(n + m + 1 + 5);
	for (int i = 1; i <= n + m + 1; i++) cin >> a[i];
	for (int i = 1; i <= n + m + 1; i++) cin >> b[i];

	int pa[2] = { Inf, Inf }, pb[2] = { Inf, Inf };
	for (int i = 0, cnt = 0; i <= n + m + 1; i++)
	{
		if (i && a[i] > b[i]) cnt++;
		if (cnt == n)
		{
			pa[0] = i;
			break;
		}
	}
	for (int i = 0, cnt = 0; i <= n + m + 1; i++)
	{
		if (i && a[i] > b[i]) cnt++;
		if (cnt == n  + 1)
		{
			pa[1] = i;
			break;
		}
	}
	for (int i = 0, cnt = 0; i <= n + m + 1; i++)
	{
		if (i && a[i] <= b[i]) cnt++;
		if (cnt == m)
		{
			pb[0] = i;
			break;
		}
	}
	for (int i = 0, cnt = 0; i <= n + m + 1; i++)
	{
		if (i && a[i] <= b[i]) cnt++;
		if (cnt == m + 1)
		{
			pb[1] = i;
			break;
		}
	}
	//cout << pa[0] << " " << pa[1] << endl;
	//cout << pb[0] << " " << pb[1] << endl;

	vector<int> prem(n + m + 1 + 5), prea(n + m + 1 + 5), preb(n + m + 1 + 5);
	for (int i = 1; i <= n + m + 1; i++)
	{
		prem[i] = prem[i - 1] + max(a[i], b[i]);
		prea[i] = prea[i - 1] + a[i];
		preb[i] = preb[i - 1] + b[i];
	}
	for (int i = 1; i <= n + m + 1; i++)
	{
		int ans = 0;
		// 来的时候已经有岗位满了
		if (i > min(pa[0], pb[0]))
		{
			if (pa[0] < pb[0])
			{
				ans = prem[pa[0]] + preb[n + m + 1] - preb[pa[0]] - b[i];
			}
			else
			{
				ans = prem[pb[0]] + prea[n + m + 1] - prea[pb[0]] - a[i];
			}
		}
		// 一个敲代码的没来
		else if (a[i] > b[i])
		{
			if (pa[1] < pb[0])
			{
				ans = prem[pa[1]] - a[i] + preb[n + m + 1] - preb[pa[1]];
			}
			else
			{
				ans = prem[pb[0]] - a[i] + prea[n + m + 1] - prea[pb[0]];
			}
		}
		// 一个测试的没来
		else
		{
			if (pb[1] < pa[0])
			{
				ans = prem[pb[1]] - b[i] + prea[n + m + 1] - prea[pb[1]];
			}
			else
			{
				ans = prem[pa[0]] - b[i] + preb[n + m + 1] - preb[pa[0]];
			}
		}
		cout << ans << " ";
	}
	cout << endl;
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
