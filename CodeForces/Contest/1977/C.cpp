#include<iostream>
#include<algorithm>
#include<map>
//#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
using ll = long long;
const int N = 2000, Inf = (1ll << 31) - 1;
int a[N + 5];
ll gcd(ll a, ll b)
{
	while (b)
	{
		a %= b;
		a = a ^ b;
		b = a ^ b;
		a = a ^ b;
	}
	return a;
}
ll LCM(ll a, ll b)
{
	return a / gcd(a, b) * b;
}

// 记整个序列的最大值为mx
// 则整个序列的LCM >= mx
// 当整个序列的LCM > mx 时, 答案为n
// 否则整个序列的LCM = mx, 这说明序列中的每个数都是mx的因数
// 且序列的任意一子序列的LCM <= mx 的
// 所以我们可以枚举LCM的未在序列里出现过的因数, 计算答案取最大值
void solve()
{
	int n;
	cin >> n;
	int mx = -Inf;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		mx = max(mx, a[i]);
	}
	for (int i = 1; i <= n; i++)
	{
		if (mx % a[i])
		{
			cout << n << endl;
			return;
		}
	}

	// 用于判断枚举到的数是否在序列里存在
	map<int, bool> mp;
	for (int i = 1; i <= n; i++)
	{
		mp[a[i]] = true;
	}

	int ans = 0;
	auto cnt = [=](ll tar)-> int
		{
			int res = 0;
			ll cur = 1;

			for (int i = 1; i <= n; i++)
			{
				if (tar % a[i]) continue;
				cur = LCM(cur, a[i]);
				res++;
			}
			res = cur == tar ? res : 0;

			// cout << tar << " " << res << endl;

			return res;
		};
	for (int i = 1; i * i <= mx; i++)
	{
		if (mx % i) continue;
		
		if (!mp[i])
			ans = max(ans, cnt(i));
		if (!mp[mx / i])
			ans = max(ans, cnt(mx / i));
	}
	cout << ans << endl;
	return;
}

int main()
{
	int t = 1;
	cin >> t;
	while (t--)
	{
		solve();
	}
	return 0;
}
