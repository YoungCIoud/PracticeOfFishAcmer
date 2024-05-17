#include<iostream>
#include<algorithm>
using namespace std;
const int N = 1e4;
int a[N+5];
int gcd(int x, int y)
{
	while (y)
	{
		x = x ^ y;
		y = x ^ y;
		x = x ^ y;
		y %= x;
	}
	return x;
}

int solve()
{
	int n; cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
	{
		if (i == 2) continue;
		a[2] /= gcd(a[2], a[i]);
	}
	return a[2];
}

int main()
{
	int t; cin >> t;
	while (t--) puts(solve() == 1 ? "Yes" : "No");
	return 0;
}
