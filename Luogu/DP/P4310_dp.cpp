#include <climits>
#include<iostream>
//#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
using ll = long long;
const int N = 1e5, Inf = INT_MAX;
int dp[32];
int main()
{
	int n;
	cin >> n;
	int ans = -Inf;
	for (int i = 1; i <= n; i++)
	{
		int a;
		cin >> a;
		int d = 1;
		for (int k = 30; ~k; k--)
		{
			if (a >> k & 1)
			{
				d = max(dp[k] + 1, d);
			}
		}
		for (int k = 30; ~k; k--)
		{
			if (a >> k & 1)
			{
				dp[k] = d;
			}
		}
		ans = max(ans, d);
	}
	cout << ans;
	return 0;
}
