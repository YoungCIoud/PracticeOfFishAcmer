#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
const int N = 2e5;
vector<int> p(N), q(N);

void solve()
{
	int n, pos=-1; cin >> n;
	for (int i = 0; i < n; i++) cin >> p[i];
	for (int i = 0; pos == -1; i++)
		if (p[i] == n) pos = i;
	// make sure that n`s index is even
	if (pos & 1) reverse(p.begin(), p.begin() + n);
	// value ans position
	priority_queue<pair<int, int>> eq, oq;
	for (int i = 0; i < n; i += 2)
	{
		eq.push({ p[i],i });
		oq.push({ p[i + 1],i + 1 });
	}
	for (int i = 1; i + i <= n; i++)
	{
		// the number at q_i is smaller when the number at p_i is bigger
		q[eq.top().second] = n / 2 + i; eq.pop();
		q[oq.top().second] = i; oq.pop();
	}

	if (pos & 1) reverse(q.begin(), q.begin() + n);
	for (int i = 0; i < n; i++) cout << q[i] << " \n"[i == n - 1];
}

int main()
{
	int t = 1;
	cin >> t;
	while (t--) solve();
	return 0;
}
