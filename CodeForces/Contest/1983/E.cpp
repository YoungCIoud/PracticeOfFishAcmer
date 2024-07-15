#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 4e5, Inf = 1e18, Mod = 1e9 + 7;
int n, k;
int qpow(int a, int p)
{
	int res = 1;
	for (; p; a = a * a % Mod, p >>= 1)
	{
		if (p & 1)
		{
			res = res * a % Mod;
		}
	}
	return res;
}
int inv(int a)
{
	return qpow(a, Mod - 2);
}

// 算出先手的期望后可以直接得出后手的期望(两者相加等于总和)
// 只用算出先手的得分期望就可以得出另一个人的得分期望
// 可以用插空的方式考虑special ball的位置
// 在n - k + 1个空中插入k个special ball
// 且每空有special ball的期望是 k / (n - k + 1)
// 先手选到空的期望是(n - k + 1 + 1 / 2)
void solve()
{
	cin >> n >> k;
	int sum_special = 0, sum_ordinary = 0;
	for (int i = 1; i <= k; i++)
	{
		int v;
		cin >> v;
		sum_special += v;
	}
	sum_special %= Mod;
	for (int i = k; i < n; i++)
	{
		int v;
		cin >> v;
		sum_ordinary += v;
	}
	sum_ordinary %= Mod;
	
	int p_special = 0;
	if (sum_special)
	{
		p_special = (sum_special * ((n - k + 2) / 2 * inv(n - k + 1) % Mod)) % Mod;
	}
	else
	{
		p_special = 0;
	}
	int p_ordinary = 0;
	if (sum_ordinary)
	{
		p_ordinary = (sum_ordinary * ((n - k + 1) / 2 * inv(n - k) % Mod)) % Mod;
	}
	else
	{
		p_ordinary = 0;
	}
	
	int ans = (p_special + p_ordinary) % Mod;
	cout << ans << " " << (Mod + (sum_special + sum_ordinary) % Mod - ans) % Mod << endl;
}

signed main()
{
	int t;
	cin >> t;
	while (t--)
	{
		solve();
	}
	return 0;
}
