#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 1e6, Inf = 1e18, Mod = 998244353;

int solve(int x, int y, int k)
{
	if (k == 0) return x;
	if (x < y)
	{
		return (x + k - 1) % (y - 1) + 1;
	}

	int r = (x + y) / y * y;
	if (r - x > k)
	{
		return x + k;
	}
	else
	{
		int _x = r;
		while (_x % y == 0)
		{
			_x /= y;
		}
		return solve(_x, y, k - (r - x));
	}
}

signed main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int a, b, c;
		cin >> a >> b >> c;
		cout << solve(a, b, c) << endl;
	}
}
