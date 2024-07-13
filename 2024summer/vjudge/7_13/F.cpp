#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 5e5, M = 1e5, Inf = 1e16, Mod = 1e9 + 7;
int n, m, k;

// 严格小于ans的数的数量
int th(int ans)
{
	int rank = 0;
	for (int i = 1; i <= n; i++)
	{
		// 找严格小于ans的数的数量, 所以这里ans需要-1
		rank += min((ans - 1) / i, m);
	}
	return rank;
}

signed main()
{
	cin >> n >> m >> k;
	int l = 1, r = n * m;
	while (l <= r)
	{
		int m = l + r >> 1;
		if (th(m) < k) l = m + 1;
		else r = m - 1;
	}
	cout << r << endl;
	return 0;
}
