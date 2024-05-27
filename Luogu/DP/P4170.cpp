#include<iostream>
#include<cstring>	//memset
#include<string>
//#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
using ll = long long;
const int N = 50, Inf = (1ll << 31) - 1;
string s;
int dp[N + 5][N + 5];
int main()
{
	cin >> s;
	int n = s.length();
	s.insert(0, "#");
	memset(dp, 0x3f, sizeof dp);
	for (int i = 1; i <= n; i++)
	{
		dp[i][i] = 1;
	}
	for (int l = 2; l <= n; l++)
	{
		for (int i = 1, j = i + l - 1; j <= n; i++, j++)
		{
			dp[i][j] = Inf;
			if (s[i] == s[j])
			{
				dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]);
			}
			else
			{
				for (int k = i; k < j; k++)
				{
					dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
				}
			}
		}
	}
	cout << dp[1][n];
	return 0;
}
