#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<queue>
#define int long long
using namespace std;
const int N = 1e6;
 
void solve()
{
	int a, b, c;
	cin >> a >> b >> c;
	int sum = a + b + c;
	if (sum & 1) return void(puts("-1"));
	int ans = 0;
	priority_queue<int> q;
	if(a)q.push(a);
	if(b)q.push(b);
	if(c)q.push(c);
	while (q.size() >= 2)
	{
		int x = q.top(); q.pop();
		int y = q.top(); q.pop();
		ans++;
		x -= 1;
		y -= 1;
		if (x) q.push(x);
		if (y) q.push(y);
	}
	cout << ans << endl;
}
 
signed main()
{
	int t = 1;
	cin >> t;
	while (t--) solve();
	return 0;
}
