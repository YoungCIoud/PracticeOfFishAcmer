#include<iostream>
//#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
using ll = long long;
const int N = 32, X = 40, Inf = (1ll << 31) - 1;
int ans[N + 5];

int main()
{
	int t = 1;
	cin >> t;
	while (t--)
	{
		int a;
		cin >> a;
		for (int i = 0; i + 1 < 32; i++)
		{
			if (a >> i & 1 && a >> i + 1 & 1)
			{
				ans[i] = -1;
				a += (1 << i + 1);
			}
			else ans[i] = a >> i & 1;
		}
		ans[31] = a >> 31 & 1;
		cout << 32 << endl;
		for (int i = 0; i < 32; i++)
		{
			cout << ans[i] << " \n"[i == 31];
		}
	}
	return 0;
}
