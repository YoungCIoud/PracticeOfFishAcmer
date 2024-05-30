#include<algorithm>
#include<iostream>
#include<map>
#include<unordered_map>
#include<string>
#include<math.h>
#include<stack>
#include<vector>
#include<queue>
 
//#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
using ll = long long;
const int N = 3e5, Inf = (1ll << 31) - 1, Mod = 1e9 + 7;
int n, m;
int type[N + 5];
vector<pair<int,int>> mate;
 
bool check(int ans)
{
	vector<int> cnt(m + 1);
	vector<int> chose;
	for (int i = n - 1; ~i; i--)
	{
		if (cnt[mate[i].second]++ >= ans) continue;
		// cout << mate[i].second << endl;
		chose.push_back(mate[i].first);
	}
	if (chose.size() < ans * m) return false;
 
	for (int i = 0, j = ans * m - 1; ~j; i++, j--)
	{
		if (chose[i] < j) return false;
	}
 
	return true;
}
 
void solve()
{
	mate.clear();
 
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		cin >> type[i];
	}
	for (int i = 1; i <= n; i++)
	{
		int tem;
		cin >> tem;
		mate.push_back({ tem, type[i] });
	}
	sort(mate.begin(), mate.end());
 
	int l = 1, r = n / m;
	while (l <= r)
	{
		int m = l + r >> 1;
		//cout << "checking " << m << endl;
		if (check(m))
		{
			//puts("OK");
			l = m + 1;
		}
		else r = m - 1;
	}
	cout << r << endl;
}
 
int main()
{
	int t = 1;
	cin >> t;
	while (t--)
	{
		solve();
	}
	return 0;
}
