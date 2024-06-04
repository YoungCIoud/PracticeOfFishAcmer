#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 2e5, A = 1e6, Inf = 1e18;

void solve()
{
	string s;
	cin >> s;
	map<int, int> cnt;
	int a = 0;
	cnt[a]++;
	int ans = 0;
	for (auto c : s)
	{
		a += (c == '(' ? 1 : -1);
		ans += cnt[a];
		cnt[a]++;
		
		// 两倍后还小于当前数的在后面一定不会被选到,所以直接清除
		while (cnt.begin()->first * 2 < a)
			cnt.erase(cnt.begin());
	}
	cout << ans << endl;
}

signed main()
{
	int t = 1;
	cin >> t;
	while (t--)
	{
		solve();
	}
}
