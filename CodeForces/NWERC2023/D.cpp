#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
vector<string> s(7);
int d, h;
double ans=0;

void dfs(int cur,int dep,vector<int> c)
{
	if (dep == d)
	{
		int cnt[24] = { 0 };
		for (int day : c)
			for (int i = 0; i < 24; i++)
				if (s[day][i] == '.') cnt[i]++;
		sort(cnt, cnt + 24, greater<int>());
		int sum=0;
		for (int i = 0; i < h; i++)
			sum += cnt[i];
		//cout << sum << endl;
		ans = max(ans, 1.0 * sum / (1.0 * d * h));
		return;
	}
	for (int i = cur + 1; i < 7; i++)
	{
		c.push_back(i);
		dfs(i, dep + 1, c);
		c.pop_back();
	}
	return;
}
int main()
{
	for (auto& i : s)
		cin >> i;
	cin >> d >> h;
	dfs(-1, 0, vector<int>());
	printf("%.9lf", ans);
	return 0;
}
