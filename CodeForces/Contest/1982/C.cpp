#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 1e5, Inf = 1e18, Mod = 998244353;
int a[N + 5];

int solve()
{
	int n, l, r;
	cin >> n >> l >> r;
	int ans = 0, sum = 0, x = 1; // 左边
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		sum += a[i];
		
		while (sum > r)
		{
			sum -= a[x++];
		}
		
		if (sum >= l)
		{
			ans++;
			x = i + 1;
			sum = 0;
		}
	}
	return ans;
}

signed main()
{
	int t;
	cin >> t;
	while (t--)
	{
		cout << solve() << endl;
	}
}
