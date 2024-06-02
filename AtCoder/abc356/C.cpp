#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 15, M = 20;
signed main()
{
	// n把钥匙 m次测试 大于k返回o
	int n, m, k;
	cin >> n >> m >> k;
	
	vector<vector<int>> r(2, vector<int>(n + 1));
	vector<int> cnt(1 << n);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			r[i][j] = rnd();
		}
	}
	for (int i = 0; i < m; i++)
	{
		int t;
		cin >> t;
		vector<bool> vis(n + 1);
		for (int j = 0; j < t; j++)
		{
			int a;
			cin >> a;
			vis[a] = true;
		}
		char result;
		cin >> result;
		for (int st = 0; st < (1 << n); st++)
		{
			int sum = 0;
			for (int bits = 0; bits < n; bits++)
				if (vis[bits + 1] && (st >> bits & 1)) sum++;
			cnt[st] += (result == 'o' ? sum >= k : sum < k);
		}
	}
	int ans = 0;
	for (int st = 0; st < (1 << n); st++)
		if (cnt[st] == m) ans++;
	cout << ans;
	return 0;
}
