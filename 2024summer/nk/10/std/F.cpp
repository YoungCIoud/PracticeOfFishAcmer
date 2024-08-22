#include <bits/stdc++.h>
using namespace std;

typedef pair <int, int> point;
#define x first
#define y second

point operator - (const point &a, const point &b) {
	return {a.x - b.x, a.y - b.y};
}

point normalize(point a) {
	assert (a.x || a.y);
	int g = gcd(a.x, a.y);
	a.x /= g;
	a.y /= g;
	if (a < point(0, 0)) a.x = -a.x, a.y = -a.y;
	return a;
}


const int N = 2e3 + 5;

int n;
vector <point> a;
bool vis[N][N];


bool add (point p) {
	auto [x, y] = p;
	if (vis[x][y]) return false;
	for (auto q : a) {
		auto [dx, dy] = normalize(q - p);
		for (int tx = x + dx, ty = y + dy;
			1 <= tx && tx <= n && 1 <= ty && ty <= n;
			tx += dx, ty += dy)
			vis[tx][ty] = 1;
		for (int tx = x - dx, ty = y - dy;
			1 <= tx && tx <= n && 1 <= ty && ty <= n;
			tx -= dx, ty -= dy)
			vis[tx][ty] = 1;
	}
	vis[x][y] = 1;
	a.push_back(p);
	return true;
}

void work() {
	cin >> n;
	a.reserve(2 * n);
	for (int i = n * n; i; i--) {
		int x, y;
		cin >> x >> y;
		cout << add ({x, y});
	}
	cout << '\n';
}

signed main() {
	ios::sync_with_stdio(false); cin.tie(0);
	int T = 1;
//	cin >> T;
	for (int ca = 1; ca <= T; ca ++) {
		work();
	}
}

