#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 1e5, Inf = 1e18, Mod = 998244353;
int a[N + 5], pri[2 * N + 5], cnt;

int b[N + 5];
void merge(int l, int m, int r)
{
	int p = l, q = m + 1, i = l;
	while (p <= m && q <= r)
	{
		if (pri[a[p]] <= pri[a[q]]) b[i++] = a[p++];
		else
		{
			cnt += (m - p + 1);
			b[i++] = a[q++];
		}
	}
	while (p <= m) b[i++] = a[p++];
	while (q <= r) b[i++] = a[q++];

	for (i = l; i <= r; i++)
		a[i] = b[i];
}

void sort(int l, int r)
{
	if (l >= r) return;
	
	int m = l + r >> 1;
	sort(l, m), sort(m + 1, r);
	merge(l, m, r);
}
bool solve()
{
	fill(pri, pri + 2 * N + 5, 0);

	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		pri[a[i]] = 1;
	}
	for (int i = 1; i <= n; i++)
	{
		int t;
		cin >> t;

		if (!pri[t]) 
		{
			for (int j = i; j < n; j++)
			{
				cin >> t;
			}
			return false;
		}
		else
		{
			pri[t] = i;
		}
	}

	cnt = 0;
	sort(1, n);
	//cout << cnt << " ";
	return (cnt % 2 == 0);
}

signed main()
{
    IOS;
	int t;
	cin >> t;
	while (t--)
	{
		puts(solve() ? "Yes" : "No");
	}
	return 0;
}
