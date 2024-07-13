#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 100, Inf = 1e18, Mod = 1e9 + 7;

void solve()
{
	int x, y, n;
	cin >> x >> y >> n;
	int ans = 0;
	if (x * 3 >= y)
		ans = n / 3 * y + n % 3 * x;
	else ans = n * x;
	cout << ans << endl;
}

signed main()
{
	int t = 1;
	while (t--)
	{
		solve();
	}
	return 0;
}
