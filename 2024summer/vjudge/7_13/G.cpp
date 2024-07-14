#include<bits/stdc++.h>
#define int unsigned long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 5e5, M = 1e5, Inf = 1e16, Mod = 1e9 + 7;
int b[64];
bool check(int x, int y)
{
	int h = 63;
	int l = 0, r = 63;
	while ((y >> l & 1) == 0) l++;
	while ((y >> r & 1) == 0) r--;
	while ((x >> h & 1) == 0) h--;
	for (int i = l; i + h <= r; i++)
	{
		if ((y >> i & 1) == 0) return false;
		bool same = true;
		for (int j = i, t = 0; t <= h && same; j++, t++)
		{
			if ((x >> t & 1) != (y >> j & 1))
			{
				same = false;
				break;
			}
		}
		if (same)
		{
			for (int j = i + h; j <= r; j++)
				if ((y >> j & 1) == 0) return false;
			return true;
		}
	}
	return false;
}

bool solve(int x, int y)
{
	if ((y & 1) == 0)
		return x == y;

	for (int i = 0; i < 64; i++)
	{
		b[i] = x >> i & 1;
	}
	int l = 0, r = 63;
	while (!b[l]) l++;
	while (!b[r]) r--;
	bool ans = false;
	if (!l)
	{
		int rev = 0;
		for (int i = l; i <= r; i++)
		{
			rev = rev << 1 | b[i];
		}
		return check(x, y) || check(rev, y);
	}
	else
	{
		int tx = 0;
		for (int i = l; i <= r; i++)
		{
			tx = tx << 1 | b[i];
		}
		return solve(tx, y) || solve(x << 1 | 1, y);
	}
}
signed main()
{
	int t = 1;
	// cin >> t;
	while (t--)
	{
		int x, y;
		cin >> x >> y;
		puts(solve(x, y) ? "Yes" : "No");
	}
	return 0;
}
