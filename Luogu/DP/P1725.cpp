#include<iostream>
#define int long long
using namespace std;
const int N = 2e5;
int n, L, R;
int a[N + 5], dp[N + 5];
int pos[N + 5], head = 1, tail = 0;

signed main()
{
	cin >> n >> L >> R;
	for (int i = 0; i <= n; i++) cin >> a[i], dp[i] = -0x3f3f3f3f;
	dp[0] = 0;
	for (int i = L; i <= n; i++)
	{
		// 将一个数插入单调队列
		while (tail >= head && dp[i - L] >= dp[pos[tail]]) tail--;
		pos[++tail] = i - L;

		while (pos[head] < i - R) head++;
		dp[i] = dp[pos[head]] + a[i];
		//cout << pos[head] << "->" << i << ":" << dp[i] << endl;
	}
	int ans = -0x3f3f3f3f;
	for (int i = n + 1 - R; i <= n; i++)
		ans = max(ans, dp[i]);
	cout << ans;
	return 0;
}
