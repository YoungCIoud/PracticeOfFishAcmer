#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;

bool solve()
{
	int n;
	cin >> n;
	string s[2];
	cin >> s[0] >> s[1];
	if ((s[0][0] & s[1][0] & 1) && (s[0][1] == '0' || s[1][1] == '0'))
	{
		s[0][0] = s[1][0] = '0';
	}
	if ((s[0][n - 1] & s[1][n - 1] & 1) && (s[0][n - 2] == '0' || s[1][n - 2] == '0'))
	{
		s[0][n - 1] = s[1][n - 1] = '0';
	}
	for (int i = 1; i < n - 1; i++)
	{
		if ((s[0][i] & s[1][i] & 1) && (s[0][i - 1] == '0' && s[0][i + 1] == '0' || s[1][i - 1] == '0' && s[1][i + 1] == '0'))
		{
			s[0][i] = s[1][i] = '0';
		}
	}
	//cout << s[0] << endl << s[1] << endl;
	
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int cnt = 0;
			while (j < n && s[i][j] & 1) cnt++, j++;
			if (cnt == 1) return false;
		}
	}
	return true;
}

signed main()
{
	int t;
	cin >> t;
	while (t--)
	{
		cout << (solve() ? "Yes" : "No") << endl;
	}
	return 0;
}
