#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 3e5, Inf = 1e18, Mod = 998244353;


signed main()
{
	int n, q;
	cin >> n >> q;
	vector<int> L(q + 1), R(q + 1);
	for (int i = 1; i <= q; i++)
		cin >> L[i];
	for (int i = 1; i <= q; i++)
		cin >> R[i];

	// build a tree according to sequence L and R
	vector<pair<int,int>> tr(n + 1);
	vector<bool> vis(n + 1);
	vis[n] = true;
	for (int i = 1; i <= q; i++)
	{
		if (vis[L[i]])
		{
			if (tr[L[i]].second)
				tr[R[i]].second = tr[L[i]].second;
			tr[L[i]].second = R[i];
			vis[R[i]] = true;
		}
		else
		{
			if (tr[R[i]].first)
				tr[L[i]].first = tr[R[i]].first;
			tr[R[i]].first = L[i];
			vis[L[i]] = true;
		}
	}
	vector<int> se(q + 2);
	int cnt = 0;
	auto build = [&](auto self, int cur) -> void
		{
			if (!cur) return;

			self(self, tr[cur].first);
			se[++cnt] = cur;
			self(self, tr[cur].second);
		};
	build(build, n);

	//for (int i = 1; i <= q + 1; i++)
	//	cout << se[i] << " ";
	//cout << endl;

	vector<int> sum(n + 1);
	for (int i = 1; i <= q; i++)
	{
		sum[max(se[i], se[i + 1])]++;
	}
	sum[se[1]]++, sum[se[q + 1]]++;

	// work out the answer;
	int ans = 1, bukets = 0;
	for (int i = n; i; i--)
	{
		if (vis[i]) bukets += sum[i];
		else
		{
			ans = ans * bukets % Mod;
			bukets++;
		}
	}
	cout << ans << endl;

	return 0;
}
