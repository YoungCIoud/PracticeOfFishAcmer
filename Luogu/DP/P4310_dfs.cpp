#include <climits>
#include<iostream>
//#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
using ll = long long;
const int N = 1e5, Inf = INT_MAX;
int a[N + 5];
int val[N + 5];
int dfs(int cur)
{
	if (val[cur]) return val[cur];

	val[cur] = 1;
	for (int i = cur - 1; i && val[cur] <= i; i--)
	{
		if (a[i] & a[cur])
		{
			val[cur] = max(val[cur], dfs(i) + 1);
		}
	}
	return val[cur];
}
int main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	int ans = -Inf;
	for (int i = 1; i <= n; i++)
	{
		ans = max(ans, dfs(i));
	}
	cout << ans;
	return 0;
}
