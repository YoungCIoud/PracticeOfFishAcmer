#include <bits/stdc++.h>

using namespace std;

constexpr int maxn = (1 << 18) + 5;

vector<int> vec[21];
map<vector<int>, int> id_tbl;
int vec_cnt = 0;

void dfs(vector<int> v, int c) {
	if (!c) {
		sort(v.begin(), v.end());
		vec[vec_cnt] = v;
		id_tbl[v] = vec_cnt++;
		return;
	}

	while ((int) v.size() <= 3) {
		dfs(v, c - 1);
		v.push_back(c);
	}
}

struct state {
	int s;
	long long a, b;
	// s >= 20 -> ready to draw the second one

	long long calc(long long wa, long long wb) const {
		return wa * a + wb * b;
	}

	long long get_cnt() const {
		return a + b;
	}
} trans[4][41];

struct node {
	state st[41];

	void init(int c) {
		memcpy(st, trans[c], sizeof(st));
	}

	void clear() {
		for (int i = 0; i < 40; i++)
			st[i] = (state) {i, 0, 0};
	}
	
	void merge(const node &u, const node &v) {
		for (int i = 0; i < 40; i++) {
			state su = u.st[i];
			state sv = v.st[su.s];

			st[i] = (state) {sv.s, su.a + sv.a, su.b + sv.b};
		}
	}
	
	node &operator += (const node &other) {
		node res;
		res.merge(*this, other);
		return *this = res;
	}
} seg[maxn];

state work(int s, int u) {
	vector<int> v = vec[s % 20];
	v.push_back(u);
	sort(v.begin(), v.end());

	if ((int) v.size() < 4 && s < 20)
		return (state) {id_tbl[v] + 20, 0, 0};

	int c[4] = {0};
	for (int x : v)
		c[x]++;
	
	c[0] = 114;
	int k = 0;
	for (int i = 1; i <= 3; i++)
		if (c[i] && c[i] < c[k])
			k = i;
	
	if (c[k] == 4)
		return (state) {0, 1, 0};
	
	for (int i = 0; i < (int) v.size(); i++)
		if (v[i] == k) {
			v.erase(v.begin() + i);
			break;
		}
	
	assert(id_tbl.count(v));
	return (state) {id_tbl[v], 0, 1};
}

void pretreat() {
	dfs(vector<int>(), 3);
	assert(vec[0].empty());
	assert(vec_cnt == 20);

	// for (int i = 0; i < 20; i++) {
	// 	cout << "vec[" << i << "] = {";
		
	// 	for (int x : vec[i])
	// 		cout << " " << x;
		
	// 	cout << " }" << endl;
	// }

	for (int c = 1; c <= 3; c++)
		for (int i = 0; i < 40; i++) {
			trans[c][i] = work(i, c);

			// cout << "work(" << i << ", " << c << ") = " << trans[c][i].s << endl;
		}
}

int seq[maxn];

void build(int l, int r, int o) {
	if (l == r) {
		seg[o].init(seq[l]);
		return;
	}

	int mid = (l + r) / 2;

	build(l, mid, o * 2);
	build(mid + 1, r, o * 2 + 1);

	seg[o].merge(seg[o * 2], seg[o * 2 + 1]);
}

void modify(int l, int r, int o, int p, int c) {
	if (l == r) {
		seg[o].init(c);
		return;
	}

	int mid = (l + r) / 2;

	if (p <= mid)
		modify(l, mid, o * 2, p, c);
	else
		modify(mid + 1, r, o * 2 + 1, p, c);
	
	seg[o].merge(seg[o * 2], seg[o * 2 + 1]);
}

node tmp;

void query_sum(int l, int r, int o, int s, int t) {
	if (s <= l && t >= r) {
		tmp += seg[o];
		return;
	}

	int mid = (l + r) / 2;

	if (s <= mid)
		query_sum(l, mid, o * 2, s, t);
	if (t > mid)
		query_sum(mid + 1, r, o * 2 + 1, s, t);
}

state cur;

long long binary(int l, int r, int o, int dmga, int dmgb, long long hp) {
	if (l == r) {
		cur.a += seg[o].st[cur.s].a;
		cur.b += seg[o].st[cur.s].b;
		cur.s = seg[o].st[cur.s].s;
		// cout << "l = " << l << "  sss = " << sss << "  fuc = " << fuc << "  ans = " << cur.a + cur.b << endl << flush;
		// assert(l - sss + 1 == cur.a + cur.b - fuc);
		return cur.a + cur.b;
	}

	state ns = cur;
	ns.s = seg[o * 2].st[cur.s].s;
	ns.a += seg[o * 2].st[cur.s].a;
	ns.b += seg[o * 2].st[cur.s].b;

	int mid = (l + r) / 2;
	if (ns.calc(dmga, dmgb) >= hp)
		return binary(l, mid, o * 2, dmga, dmgb, hp);
	else {
		cur = ns;
		return binary(mid + 1, r, o * 2 + 1, dmga, dmgb, hp);
	}
}

long long query(int l, int r, int o, int s, int t, int dmga, int dmgb, long long hp) {
	if (s <= l && t >= r) {
		state ns = cur;
		ns.a += seg[o].st[cur.s].a;
		ns.b += seg[o].st[cur.s].b;
		ns.s = seg[o].st[cur.s].s;

		if (ns.calc(dmga, dmgb) >= hp) {
			// sss = s;
			return binary(l, r, o, dmga, dmgb, hp);
		}
		else {
			cur = ns;
			return 0;
		}
	}

	int mid = (l + r) / 2;
	if (s <= mid) {
		long long tmp = query(l, mid, o * 2, s, t, dmga, dmgb, hp);
		if (tmp)
			return tmp;
	}
	return query(mid + 1, r, o * 2 + 1, s, t, dmga, dmgb, hp);
}

signed main() {

	ios::sync_with_stdio(false);

	pretreat();

	int n, m;
	cin >> n >> m;

	for (int i = 1; i <= n; i++)
		cin >> seq[i];
	
	build(1, n, 1);

	while (m--) {
		int op;
		cin >> op;

		if (op == 1) {
			int p, x;
			cin >> p >> x;
			modify(1, n, 1, p, x);
			seq[p] = x;
		}
		else {
			int l, r;
			long long h;
			int A, B;
			cin >> l >> r >> h >> A >> B;

			// cout << "wa = " << A << " wb = " << B << endl;

			tmp.clear();
			query_sum(1, n, 1, l, r);
			
			state o = (state) {0, 0, 0};
			bool vis[41] = {false};
			state first[41];
			memset(first, 0, sizeof(first));

			long long val = 0;
			bool no_cycle = false;
			while (!vis[o.s]) {
				vis[o.s] = true;
				first[o.s] = o;

				long long delta = tmp.st[o.s].calc(A, B);

				if (val + delta >= h) {
					cur = o;
					no_cycle = true;
					break;
				}
				
				o.a += tmp.st[o.s].a;
				o.b += tmp.st[o.s].b;
				o.s = tmp.st[o.s].s;
				
				val += delta;
				// cout << "val += " << delta << endl;
			}

			// cout << "now val = " << val << "o.calc = " << o.calc(A, B) << endl;
			
			if (!no_cycle) {
				cur = first[o.s];
				state period = (state) {-1, o.a - cur.a, o.b - cur.b};

				if (period.calc(A, B) == 0) {
					cout << "-1\n";
					continue;
				}

				long long cnt = (h - val - 1) / period.calc(A, B);

				cur.a += cnt * period.a;
				cur.b += cnt * period.b;
				val += (cnt - 1) * period.calc(A, B);

				// cout << "cnt = " << cnt << " wa = " << A << " wb = " << B << " period = (" << period.a << ", " << period.b << ") pattern = " << period.calc(A, B) << " val = " << val << endl;

				// cout << "val = " << val << "cur.calc = " << cur.calc(A, B) << endl << flush;

				assert(val == cur.calc(A, B));

				while (true) {
					long long delta = tmp.st[cur.s].calc(A, B);
					if (val + delta >= h)
						break;
					
					val += delta;
					cur.a += tmp.st[cur.s].a;
					cur.b += tmp.st[cur.s].b;
					cur.s = tmp.st[cur.s].s;
				}
			}

			// fuc = cur.a + cur.b;

			cout << query(1, n, 1, l, r, A, B, h) << '\n';

			// cout << "a = " << cur.a << " b = " << cur.b << " total = " << cur.calc(a, b) << endl << flush;

			// assert(cur.calc(a, b) >= h);
		}
	}
	
	return 0;
}
