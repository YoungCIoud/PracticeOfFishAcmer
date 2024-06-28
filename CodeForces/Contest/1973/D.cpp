#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 1e4, Inf = 1e18, Mod = 998244353;
// 找到一个最大的m
// 使得可以将序列分成k段，且每段的函数值都是m
// 先找到序列的最大值(最多n次可找到), 则若m存在, 必然是最大值的倍数
// 考虑当将序列分成k段m可能取到的最大值, m = max * (n / k)
// 此时k整除n且每段中都含有max

signed main()
{
	int t = 1;
	cin >> t;
	while (t--)
	{
		int n, k;
		cin >> n >> k;
		int mx = n + 1;
		int l = 1, r = n + 1;
		while (r == n + 1)
		{
			mx--;
			cout << "? " << l << " " << mx * n << endl;
			cin >> r;
		}

		int ans = mx * (n / k);
		for (ans; ans >= mx; ans -= mx)
		{
			int cnt = 1;
			for (cnt = 0, l = 1, r = 0; cnt < k && n - r >= (ans / mx) * (k - cnt); cnt++, l = r + 1)
			{
				cout << "? " << l << " " << ans << endl;
				cin >> r;
			}
			if (cnt == k && r == n) break;
		}
		cout << "! " << (ans >= mx ? ans : -1) << endl;
		cin >> ans;
	}
	return 0;
}
