#include<iostream>
#include<algorithm>
using namespace std;
const int N = 1e5;
int a[N + 5], b[N + 5], p[N + 5], cnt = 1;
int dp[N + 5];

int main()
{
	int n; cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i], p[b[i]] = cnt++;

	// 将问题转换成求最长公共子序列
	int len = 0;
	for (int i = 1; i <= n; i++)
	{
		if (p[a[i]] > p[dp[len]]) dp[++len] = a[i];
		else
			dp[upper_bound(dp + 1, dp + len + 1, a[i], [](int x, int y) {
				return p[x] < p[y];
				}) - dp] = a[i];
	}
	cout << len;
	return 0;
}
