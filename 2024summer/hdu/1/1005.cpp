// 注意对称性和一些排列组合
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using i64 = long long;
const int Mod = 998244353, N = 1e7;
i64 f[N + 5], invf[N + 5], inv2;
i64 qpow(i64 a, int p)
{
	i64 res = 1;
	for (; p; p >>= 1, a = a * a % Mod)
		if (p & 1)
			res = res * a % Mod;
	return res;
}

i64 inv(i64 x)
{
	return qpow(x, Mod - 2);
}

i64 solve()
{
	int n = 0, odd = 0;
	std::cin >> n;
	std::string s;
	std::vector<i64> cnt(n);
	for (i64& i : cnt)
	{
		std::cin >> s >>  i;
		odd += (i & 1);
	}
	if (odd >= 2)
		return inv2;
	
	i64 p = 0, m1 = 1, m2 = 1, s1 = 0, s2 = 0;
	for (auto i : cnt)
	{
		m1 = m1 * f[i] % Mod;
		s1 += i;

		i /= 2;

		m2 = m2 * invf[i] % Mod;
		s2 += i;
	}
	p = m1 * f[s2] % Mod * m2 % Mod * invf[s1] % Mod;

	if (odd) // 和为奇数
		return (1 + p) * inv2 % Mod;
	else // 和为偶数
		return  (1 - p + Mod) * inv2 % Mod;
}

int main()
{
	inv2 = inv(2ll);
	f[0] = 1; // 阶乘
	for (int i = 1; i <= N; i++)
		f[i] = f[i - 1] * i % Mod;
	invf[N] = inv(f[N]);
	for (int i = N - 1; ~i; i--) // 阶乘逆元
		invf[i] = invf[i + 1] * (i + 1) % Mod;

	int t = 1;
	std::cin >> t;
	while (t--)
	{
		std::cout << solve() << '\n';
	}
	return 0;
}
