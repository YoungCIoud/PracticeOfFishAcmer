#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 2e5, Inf = 1e18, Mod = 998244353;
// option 1: c = c + ai
// option 2: c = |c + ai|
// 在 c + ai为正数的情况下都可以使用option 1,使用option 2是无意义的
// 在 c + ai为负数时使用option 2才是有意义的,此时我们希望c尽可能的小
// 假设在某次最后一次选择了option 2,则考虑它之前的操作
// 注意到 A <= |A|, 所以若在最后以一次option 2之前还使用了option 2
// c的值一定大于等于只使用option 1的c的值,所以只使用一次option 2.

int a[N + 5], p2[N + 5];
void solve()
{
	int n = 0, sum = 0, mn = 0;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		sum += a[i];
		mn = min(mn, sum);
	}

	if (mn == 2)
	{
		cout << p2[n] << endl;
		return;
	}

	sum = 0;
	int cnt = 0, ans = 0;
	for (int i = 1; i <= n; i++)
	{
		sum += a[i];
		// cnt 是前一部分可以两种操作任选的数量, n - i 是后面的
		if (sum == mn) ans = (ans + p2[cnt + (n - i)]) % Mod;
		if (sum >= 0) cnt++;
	}
	cout << ans << endl;
}

signed main()
{
	p2[0] = 1;
	for (int i = 1; i <= N; i++)
	{
		p2[i] = p2[i - 1] * 2 % Mod;
	}
	int t = 1;
	cin >> t;
	while (t--)
	{
		solve();
	}
	return 0;
}
