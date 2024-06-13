#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 2e5, Inf = 1e18, Mod = 998244353;
// 到第i个数时的最大值/最小值
// int dp[N + 5][2];
int a[N + 5], pre[N +5];

// option 1: c = c + ai
// option 2: c = |c + ai|
// 在 c + ai为正数的情况下都可以使用option 1,使用option 2是无意义的
// 在 c + ai为负数时使用option 2才是有意义的,此时我们希望c尽可能的小
// 假设在某次最后一次选择了option 2,则考虑它之前的操作
// 注意到 A <= |A|, 所以若在最后以一次option 2之前还使用了option 2
// c的值一定大于等于只使用option 1的c的值,所以只使用一次option 2.

void solve()
{
	//int n; cin >> n;
	//for (int i = 1, a; i <= n; i++)
	//{
	//	cin >> a;
	//	// minmum
	//	dp[i][0] = dp[i - 1][0] + a;

	//	// maximum
	//	dp[i][1] = max(dp[i - 1][1] + a, abs(dp[i - 1][0] + a));
	//}
	//// dp[n][1]就是能组合出来的最大值
	//cout << dp[n][1] << endl;
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		pre[i] = pre[i - 1] + a[i];
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		int res = abs(pre[i - 1] + a[i]) + pre[n] - pre[i];
		ans = max(ans, res);
	}
	cout << ans << endl;
}

signed main()
{
	int t = 1;
	cin >> t;
	while (t--)
	{
		solve();
	}
	return 0;
}
