#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<queue>
#define int long long
using namespace std;
const int N = 1e5;
int n,a[N + 5];
 
bool check(int m)
{
	bool sum[20] = { 0 };
	int cnt[20] = { 0 };
	for (int i = 1; i <= m; i++)
	{
		for (int j = 0; j < 20; j++)
			if ((a[i] >> j) & 1) sum[j] = true, cnt[j]++;
	}
	for (int i = m+1; i <= n; i++)
	{
		for (int j = 0; j < 20; j++)
			if ((a[i - m] >> j) & 1) cnt[j]--;
		for (int j = 0; j < 20; j++)
			if ((a[i] >> j) & 1) cnt[j]++;
		for (int j = 0; j < 20; j++)
			if (sum[j] ^ bool(cnt[j])) return false;
	}
	return true;
}
 
void solve()
{
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	int l = 1, r = n;
	while (l <= r)
	{
		int m = l + r >> 1;
		if (check(m)) r = m - 1;
		else l = m + 1;
	}
	cout << l << endl;
}
 
signed main()
{
	int t = 1;
	cin >> t;
	while (t--) solve();
	return 0;
}
