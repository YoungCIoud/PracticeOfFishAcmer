#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int Mod = 998244353;

signed main()
{
	int n, m;
	cin >> n >> m;
	int ans = 0;
	for (int bits = 0, high = n >> 1, low = 0, mid = n & 1; bits < 60; bits++)
	{
		if (m >> bits & 1)
		{
			ans += high * (1ll << bits) % Mod + mid * (low + 1) % Mod;
			ans %= Mod;
		}
		low |= (mid << bits);
		mid = high & 1;
		high >>= 1;
	}
	cout << ans;
	return 0;
}
