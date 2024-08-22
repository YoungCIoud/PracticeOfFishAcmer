#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair <int, int> pii;


const int INF = 0x3f3f3f3f;

void work() {
	int n, m;
	cin >> n >> m;

	int K = int(pow(10, n));

	auto check = [&](int x, int l, int r, int k) {
		for (int i = 0, cur = 1; i < n; i++, cur *= 10) {
			if (l <= i && i <= r) {
				int digit = x / cur % 10;
				x -= digit * cur;
				digit = (digit + (k ? 9 : 1)) % 10;
				x += digit * cur;
			}
		}
		return x;
	};
	auto diff = [&](int x, int y) {
		int ret = 0;
		for (int i = 0, cur = 1; i < n; i++, cur *= 10) {
			int digit = x / cur % 10 - y / cur % 10;
			if (digit < 0) digit += 10;
			ret += cur * digit;
		}
		return ret;
	};
	vector dis(2, vector (K, INF));
	queue <pair <int, int>> q;
	dis[0][0] = 0;
	q.push({0, 0});

	while (!q.empty()) {
		auto [d, x] = q.front(); q.pop();
		for (int i = 0; i < n; i++) {
			for (int j = i; j < n; j++) {
				for (int k = 0; k < 2; k++) {
					auto tx = check(x, i, j, k);
					if (dis[d ^ 1][tx] > dis[d][x] + 1) {
						dis[d ^ 1][tx] = dis[d][x] + 1;
						q.push({d ^ 1, tx});
					}
				}
			}
		}
	}
	vector < pair <int, int > > chk;
	for (int i = 1; i <= m; i++) {
		int x, y;
		cin >> x >> y;
		chk.push_back({x, y});
	}
	vector <int> ans;
	for (int i = 0; i < K; i++) {
		bool flag = true;
		for (auto [x, y] : chk) {
			int delta = diff (x, i);
			if (dis[y % 2][delta] > y) {
				flag = false;
				break;
			}
		}
		if (flag) ans.push_back(i);
	}
	if (!ans.size()) cout << "IMPOSSIBLE\n";
	else if (ans.size() > 1) cout << "MANY\n";
	else {
		string w = to_string(ans[0]);
		while ((int) w.size() < n) w = '0' + w;
		cout << w << '\n';
	}
}

int main() {
	int T = 1;
	cin >> T;
	for (int ca = 1; ca <= T; ca ++) {
		work();
	}
}

