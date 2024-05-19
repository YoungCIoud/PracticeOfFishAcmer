#include<iostream>
using namespace std;
bool vis[25 * 25 + 5];
int ans = 0;
// 有n条平行的线且已积累的交点的和为sum
void solve(int n,int sum)
{
	if (n == 0 && !vis[sum])
		ans++, vis[sum] = true;
	// 从n条平行的线中取出i条
	for (int i = 1; i <= n; i++)
		solve(n - i, i * (n - i) + sum);
}

int main()
{
	int n;
	cin >> n;
	solve(n,0);
	cout << ans;
	return 0;
}
