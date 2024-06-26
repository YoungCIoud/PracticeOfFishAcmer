#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 20, Inf = 1e18, Mod = 998244353;

void solve()
{
	int n, k;
	cin >> n >> k;

	if (n == 1)
	{
		if (k) return void(puts("No"));
		else
		{
			puts("Yes");
			puts("1");
			return;
		}
	}

	if (k % 2)
	{
		puts("No");
		return;
	}
	int ind = 1, sum = 0;
	while (sum + (n + 1 - ind * 2) * 2 < k && ind <= n / 2)
	{
		sum += (n + 1 - ind * 2) * 2;
		ind++;
	}
	if (ind > n / 2)
	{
		puts("No");
		return;
	}
	puts("Yes");
	for (int i = 1; i < ind; i++)
		cout << i + ind << " ";
	int num = ind * 2;
	while (sum < k)
	{
		cout << num << " ";
		sum += 2;
		num++;
	}
	cout << ind << " ";
	for (; num <= n; num++)
		cout << num << " ";
	for (int i = ind - 1; i; i--)
		cout << i << " ";
	cout << endl;
}

signed main()
{
	int t = 1;
	cin >> t;
	while (t--)
	{
		solve();
	}
	return 0;
}
