#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int Inf = 0x3f3f3f3f;
int n;
const int N = 1e2;
int a[2*N + 5], sum[2*N + 5];
int dp[2*N + 5][2*N + 5], s[N + 5][N + 5];

int min(int a, int b) {
	return a < b ? a : b;
}
int max(int a, int b) {
	return a > b ? a : b;
}

int solve(int inf,int fun(int a,int b))
{
	for (int i = 1; i <= 2 * n; i++)
		for (int j = 1; j <= 2 * n; j++)
			dp[i][j] = inf;
	for (int i = 1; i <= 2 * n; i++) dp[i][i] = 0;
	for (int l = 2; l <= n; l++)
		for (int i = 1, j = i + l - 1; j < 2 * n; i++, j++)
			for (int k = i; k < j; k++)
				dp[i][j] = fun(dp[i][j], dp[i][k] + dp[k + 1][j] + sum[j] - sum[i - 1]);
	int ans = inf;
	for (int i = 1; i < n; i++)
		ans = fun(ans, dp[i][i + n - 1]);
	return ans;
}

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i], sum[i] = sum[i - 1] + a[i];
	for (int i = 1; i <= n; i++)
		sum[n + i] = sum[n + i - 1] + a[i];
	cout << solve(Inf, min) << endl << solve(-Inf, max);
	return 0;
}
