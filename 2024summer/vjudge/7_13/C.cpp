#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 5e5, M = 1e5, Inf = 1e16, Mod = 1e9 + 7;

bool solve()
{
	int n, m, k;
	cin >> n >> m >> k;
	if (n & 1)
	{
		if (k * 2 < m) return false;
		k -= m / 2;
		n--;
	}
	if (m & 1) m--;
	if (k & 1 || k * 2 > n * m) return false;
	return true;
}

signed main()
{
	int t = 1;
	cin >> t;
	while (t--)
	{
		puts(solve() ? "Yes" : "No");
	}
	return 0;
}
