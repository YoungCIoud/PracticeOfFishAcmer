#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int Inf = 1e18, Mod = 998244353;
// 1000000000000000000
int qpow(int a, int p)
{
	int res = 1;
	for (; p; a = a * a % Mod, p >>= 1)
		if (p & 1) res = res * a % Mod;
	return res;
}

int inv(int a)
{
	return qpow(a, Mod - 2);
}

signed main()
{
	int n;
	cin >> n;
	__int128 p = 1;
	while (p <= n) p *= 10;
	p %= Mod;

	cout << (n % Mod * ((qpow(p, n) - 1 + Mod) % Mod) % Mod * inv(p - 1) % Mod);
	return 0;
}
