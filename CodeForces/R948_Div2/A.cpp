#include<iostream>
//#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
using ll = long long;
const int N = 500, X = 40, Inf = (1ll << 31) - 1;

int main()
{
	int t = 1;
	cin >> t;
	while (t--)
	{
		int a, b;
		cin >> a >> b;
		if (b > a)
		{
			puts("No");
		}
		else
		{
			b -= a;
			puts(b & 1 ? "No" : "Yes");
		}
	}
	return 0;
}
