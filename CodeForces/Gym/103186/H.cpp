#define ll long long
#define ull unsigned long long
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
const int M = 1e5 + 5;
ll mod = 1e9 + 7;

struct car {
	ll p, v, c;
};

bool cmp(const car& a, const car& b) {
	return a.p < b.p;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
	
	int n, k;
	cin >> n >> k;
	vector<car> f(n);
	for (int i = 0; i < n; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		f[i] = {a, b, c};
	} 
	sort(f.begin(), f.end(), cmp);
	ll l = 0, r = 4e9;
	while (l + 1 < r) {
		bool flag = true;
		ll mid = (l + r) >> 1;
		ll kind = f[0].c;
		ll d = f[0].v * mid; 
		ll left = f[0].p + d;
		ll right = f[0].p + d;
		ll tmp = LLONG_MIN;
		
		for (int i = 1; i < n; ++i) {
			d = f[i].v * mid;
			if (f[i].c == kind) {
				left = min(left, f[i].p + d);
				right = max(right, f[i].p + d);
			}
			else {
				if (left <= tmp) {
					flag = false;
					break;
				}
				tmp = right;
				left = f[i].p + d;
				right = f[i].p + d;
				kind = f[i].c;
			}
		}
		
		if (left <= tmp) {
			flag = false;
		}
		if (flag) {
			l = mid;
		}
		else {
			r = mid;
		}
	}
	
	cout << ((r == 4e9) ? -1 : l) << endl;
    return 0;
}
/*
5 2
0 10 1
5 1 1
12 -1 2
15 -1 2 
-10 5 2

5 1
10 9 1
100 99 1
99 -10 1
50 40 1
998233 -10000 1
*/
