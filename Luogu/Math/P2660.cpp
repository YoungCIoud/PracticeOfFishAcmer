#include<iostream>
#define int long long
using namespace std;

int solve(int a, int b)
{
	if (!b) return 0;
	if (a < b)
	{
		a = a ^ b;
		b = a ^ b;
		a = a ^ b;
	}
	int tim = 0;
	tim = a / b;
	return b * 4 * tim + solve(b, a - tim * b);
}

signed main()
{
	int a, b;
	cin >> a >> b;
	cout << solve(a, b);
	return 0;
}
