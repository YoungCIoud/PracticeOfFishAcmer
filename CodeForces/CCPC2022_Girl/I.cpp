#include<string>
#include<iostream>
//#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 5e3, M = 5e5, Inf = 0x3f3f3f3f;
int dp[N+5][2];
struct node
{
	bool tag;
	int nex[26];
	node()
	{
		tag = false;
		for (int i = 0; i < 26; i++)
		{
			nex[i] = 0;
		}
	}
};

node t[2][M + 5];
int cnt[2];

void insert(string s, int ind)
{
	int p = 0;
	for (int i = 0; i < s.size(); p = t[ind][p].nex[s[i++] - 'a'])
	{
		if (t[ind][p].nex[s[i] - 'a']) continue;
		t[ind][p].nex[s[i] - 'a'] = ++cnt[ind];
	}
	t[ind][p].tag = true;
}

int main()
{
	IOS;
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		string s;
		cin >> s;
		insert(s, 0);
	}
	int m;
	cin >> m;
	for (int i = 1; i <= m; i++)
	{
		string s;
		cin >> s;
		insert(s, 1);
	}
	
	string s;
	cin >> s;
	int len = s.size();
	for (int i = 0; i + i < len; i++) swap(s[i], s[len - i - 1]);
	// cout << s << endl;
	s.insert(0, "&");
	dp[0][1] = dp[0][0] = 0;
	for (int i = 1; i <= len; i++)
	{
		dp[i][0] = dp[i][1] = Inf;
		int tem;
		tem = t[0][0].nex[s[i] - 'a'];
		for (int j = i; j && tem; tem = t[0][tem].nex[s[--j] - 'a'])
		{
			// cout << "dp" << endl;
			if (t[0][tem].tag == false) continue;
			// cout << "i=" << i << " j=" << j << endl;
			dp[i][1] = min(dp[i][1], dp[j - 1][0] + 1);
		}

		tem = t[1][0].nex[s[i] - 'a'];
		for (int j = i; j && tem; tem = t[1][tem].nex[s[--j] - 'a'])
		{
			// cout << "dp" << endl;
			if (t[1][tem].tag == false) continue;
			// cout << "i=" << i << " j=" << j << endl;
			dp[i][0] = min(dp[i][0], dp[j - 1][1] + 1);
		}
	}
	int ans = min(dp[len][1], dp[len][0]);
	cout << (ans == Inf ? -1 : ans);
	return 0;
}
