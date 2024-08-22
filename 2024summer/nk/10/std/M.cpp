#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = (1 << 18) + 5, p = 998244353;

using ll = long long;
using ull = unsigned long long;
using poly = vector<int>;

int qpow(int a, int b) {
	int ans = 1;
	while (b) {
		if (b & 1)
			ans = (ll)ans * a % p;
		a = (ll)a * a % p;
		b >>= 1;
	}
	return ans;
}

int inv[MAXN];
poly omega[25];

void ntt_init(int n) {
	for (int k = 2, d = 0; k <= n; k *= 2, d++) {
		omega[d].resize(k + 1);

		int wn = qpow(3, (p - 1) / k), tmp = 1;
		for (int i = 0; i <= k; i++) {
			omega[d][i] = tmp;
			tmp = (ll)tmp * wn % p;
		}
	}

	inv[1] = 1;
	for (int i = 2; i < n; i++)
		inv[i] = (ll)(p - p / i) * inv[p % i] % p;
}

void ntt(int* c, int n, int t) {
	static ull a[MAXN];
	for (int i = 0; i < n; i++)
		a[i] = c[i];
	
	for (int i = 1, j = 0; i < n - 1; i++) {
		int k = n;
		do
			j ^= (k >>= 1);
		while (j < k);

		if (i < j)
			swap(a[i], a[j]);
	}

	for (int k = 1, d = 0; k < n; k *= 2, d++) {
		if (d == 16)
			for (int i = 0; i < n; i++)
				a[i] %= p;
		
		for (int i = 0; i < n; i += k * 2)
			for (int j = 0; j < k; j++) {
				int w = omega[d][t > 0 ? j : k * 2 - j];
				ull u = a[i + j], v = w * a[i + j + k] % p;
				
				a[i + j] = u + v;
				a[i + j + k] = u - v + p;
			}
	}

	if (t > 0) {
		for (int i = 0; i < n; i++)
			c[i] = a[i] % p;
	}
	else {
		int inv = qpow(n, p - 2);
		for (int i = 0; i < n; i++)
			c[i] = a[i] * inv % p;
	}
}

int get_ntt_n(int n) { // not inclusive
	int ntt_n = 1;
	while (ntt_n < n)
		ntt_n *= 2;
	return ntt_n;
}

poly poly_calc(const poly& u, const poly& v, function<int(int, int)> op) {
	static int a[MAXN], b[MAXN], c[MAXN];

	int n = (int)u.size();

	copy(u.data(), u.data() + n, a);
	fill(a + n, a + n * 2, 0);
	copy(v.data(), v.data() + n, b);
	fill(b + n, b + n * 2, 0);
	
	ntt(a, n * 2, 1);
	ntt(b, n * 2, 1);

	for (int i = 0; i < n * 2; i++)
		c[i] = op(a[i], b[i]);
	
	ntt(c, n * 2, -1);

	return poly(c, c + n * 2);
}

poly poly_mul(const poly& u, const poly& v) {
	return poly_calc(u, v, [](int a, int b) { return (ll)a * b % p; });
}

poly poly_inv(const poly& a) {
	poly c{qpow(a[0], p - 2)};

	for (int k = 2; k <= (int)a.size(); k *= 2) {
		c.resize(k);

		poly b(a.data(), a.data() + k);
		c = poly_calc(b, c, [](int bi, int ci) {
			return ((2 - (ll)bi * ci) % p + p) * ci % p;
		});
		fill(c.data() + k, c.data() + k * 2, 0);
	}

	c.resize(a.size());
	return c;
}

poly poly_derivative(const poly& a) {
	poly c(a.size());
	for (int i = 1; i < (int)a.size(); i++)
		c[i - 1] = (ll)a[i] * i % p;
	return c;
}

poly poly_integrate(const poly& a) {
	poly c(a.size());
	for (int i = 1; i < (int)a.size(); i++)
		c[i] = (ll)a[i - 1] * inv[i] % p;
	return c;
}

poly poly_ln(const poly& a) {
	poly c = poly_mul(poly_derivative(a), poly_inv(a));
	c.resize(a.size());
	return poly_integrate(c);
}

poly poly_exp(const poly& a) {
	poly c{1};

	for (int k = 2; k <= (int)a.size(); k *= 2) {
		c.resize(k);

		poly b = poly_ln(c);
		for (int i = 0; i < k; i++) {
			b[i] = a[i] - b[i];
			if (b[i] < 0)
				b[i] += p;
		}
		(++b[0]) %= p;

		c = poly_mul(b, c);
		fill(c.data() + k, c.data() + k * 2, 0);
	}

	c.resize(a.size());
	return c;
}

poly poly_pow(const poly& a, int k) {
	poly c = poly_ln(a);
	for (int i = 0; i < (int)c.size(); i++)
		c[i] = (ll)c[i] * k % p;
	return poly_exp(c);
}

poly poly_auto_mul(poly a, poly b) {
	int res_len = (int)a.size() + (int)b.size() - 1;
	int ntt_n = get_ntt_n(res_len);

	a.resize(ntt_n);
	b.resize(ntt_n);

	ntt(a.data(), ntt_n, 1);
	ntt(b.data(), ntt_n, 1);

	for (int i = 0; i < ntt_n; i++)
		a[i] = (ll)a[i] * b[i] % p;
	
	ntt(a.data(), ntt_n, -1);
	a.resize(res_len);
	return a;
}

void dft_2d(vector<poly>& a, int ntt_n, int ntt_m) {
	int n = (int)a.size();

	a.resize(ntt_n);
	for (int i = 0; i < ntt_n; i++) {
		a[i].resize(ntt_m);

		if (i < n)
			ntt(a[i].data(), ntt_m, 1);
	}

	for (int j = 0; j < ntt_m; j++) {
		poly t(ntt_n);

		for (int i = 0; i < n; i++)
			t[i] = a[i][j];
		
		ntt(t.data(), ntt_n, 1);

		for (int i = 0; i < ntt_n; i++)
			a[i][j] = t[i];
	}
}

void idft_2d(vector<poly>& a, int n, function<bool(int)> filter) {
	int ntt_n = (int)a.size(), m = (int)a[0].size();

	for (int j = 0; j < m; j++) {
		poly t(ntt_n);
		for (int i = 0; i < ntt_n; i++)
			t[i] = a[i][j];
		
		ntt(t.data(), ntt_n, -1);

		for (int i = 0; i < n; i++)
			a[i][j] = t[i];
	}

	a.resize(n);
	for (int i = 0; i < n; i++)
		if (filter(i))
			ntt(a[i].data(), m, -1);
}

poly bostan_mori(const poly& f) {
	int n = (int)f.size() - 1;
	vector<poly> a(n + 1), b(n + 1);

	for (int i = 0; i <= n; i++) {
		a[i] = {0};
		b[i] = {(p - f[i]) % p};
	}

	bool a00 = true;
	int m = 1;
	while (n) {
		vector<poly> ac(a), bc(b);
		for (int i = 0; i <= n; i++)
			for (int j = 0; j < m; j++) {
				if (a00) {
					int d = i % 2 ? p - b[i][j] : b[i][j];
					(a[i][j] += d) %= p;
				}

				if (i % 2 == 0)
					b[i][j] = b[i][j] * 2 % p;
				else
					b[i][j] = 0;
			}
		
		int ntt_n = get_ntt_n(n * 2 + 1);

		dft_2d(ac, ntt_n, m * 2);
		dft_2d(bc, ntt_n, m * 2);

		for (int i = 0; i < ntt_n; i++)
			for (int j = 0; j < m * 2; j++)
				ac[i][j] = (ll)ac[i][j] * bc[(i + ntt_n / 2) & (ntt_n - 1)][j] % p;
		
		for (int i = 0; i < ntt_n / 2; i++)
			for (int j = 0; j < m * 2; j++)
				bc[i][j] = (ll)bc[i][j] * bc[i + ntt_n / 2][j] % p;
		
		bc.resize(ntt_n / 2);

		idft_2d(ac, n + 1, [n](int i) { return i % 2 == n % 2; });
		idft_2d(bc, n / 2 + 1, [](int i) { return true; });

		for (int i = 0; i <= n; i++)
			if (i % 2 == n % 2) {
				a[i].resize(m * 2);

				for (int j = 1; j < m * 2; j++)
					(a[i][j] += ac[i][j - 1]) %= p;
				
				a[i / 2].swap(a[i]);
			}
		
		for (int i = 0; i <= n / 2; i++) {
			b[i].swap(b[i * 2]);
			b[i].resize(m * 2);

			for (int j = 1; j < m * 2; j++)
				(b[i][j] += bc[i][j - 1]) %= p;
		}

		a00 &= !(n % 2);
		n /= 2;
		m *= 2;

		a.resize(n + 1);
		b.resize(n + 1);
	}

	for (int i = (int)f.size() - 1; i; i--) {
		a[0][i] = a[0][i - 1];
		b[0][i] = b[0][i - 1];
	}
	a[0][0] = b[0][0] = 1;

	poly res = poly_mul(a[0], poly_inv(b[0]));
	res.resize(f.size());
	return res;
}

poly poly_composite_inversion(const poly& g) {
	assert(!g[0] && g[1]);

	int n = (int)g.size() - 1;

	int g1_inv = qpow(g[1], p - 2);
	poly t(n + 1);
	for (int i = 1; i <= n; i++)
		t[i] = (ll)g[i] * g1_inv % p;
	
	poly res = bostan_mori(t);

	for (int i = 0, pw = 1; i < n; i++) {
		t[i] = (ll)n * inv[n - i] % p * res[n - i] % p * pw % p;
		pw = (ll)pw * g1_inv % p;
	}

	int ntt_n = 1;
	while (ntt_n <= n)
		ntt_n *= 2;
	t.resize(ntt_n);

	t = poly_pow(t, p - inv[n]);

	poly f(n + 1);
	for (int i = 1; i <= n; i++)
		f[i] = (ll)t[i - 1] * g1_inv % p;
	return f;
}

vector<poly> bostan_mori_comp(int n, const poly& a, vector<poly> b) {
	if (!n) {
		int n0 = (int)a.size(), m = (int)b[0].size();

		b[0].insert(b[0].begin(), 1);
		b[0].resize(get_ntt_n(n0));
		poly b_inv = poly_inv(b[0]);
		b_inv.resize(a.size());

		poly t = poly_auto_mul(a, b_inv);
		poly res(m);
		for (int i = 0; i < n0; i++)
			res[i + m - n0] = t[i];
		
		return {res};
	}

	int ntt_n = get_ntt_n(n * 2 + 1);
	int m = (int)b[0].size();

	vector<poly> q = b;
	dft_2d(b, ntt_n, m * 2);

	vector<poly> c(ntt_n);
	for (int i = 0; i < ntt_n; i++)
		c[i] = b[(i + ntt_n / 2) & (ntt_n - 1)];
	
	b.resize(ntt_n / 2);

	for (int i = 0; i < ntt_n / 2; i++)
		for (int j = 0; j < m * 2; j++)
			b[i][j] = (ll)b[i][j] * c[i][j] % p;
	
	idft_2d(b, n / 2 + 1, [](int i) { return true; });

	for (int i = 0; i <= n / 2; i++) {
		for (int j = m * 2 - 1; j; j--)
			b[i][j] = b[i][j - 1];
		b[i][0] = 0;

		for (int j = 0; j < m; j++)
			b[i][j] = (b[i][j] + q[i * 2][j] * 2 % p) % p;
	}

	b.resize(n / 2 + 1);

	vector<poly> res = bostan_mori_comp(n / 2, a, move(b));

	vector<poly> t = res;
	dft_2d(t, ntt_n / 2, m * 2);

	for (int i = 0; i < ntt_n; i++)
		for (int j = 0; j < m * 2; j++)
			c[i][j] = (ll)t[i & (ntt_n / 2 - 1)][j] * c[i][j] % p;
	
	idft_2d(c, n + 1, [](int i) { return true; });

	t = vector<poly>(n + 1);
	for (int i = 0; i <= n; i++) {
		t[i].resize(m);

		for (int j = 0; j < m; j++)
			t[i][j] = c[i][j + m - 1];
		
		if (i % 2 == 0)
			for (int j = 0; j < m; j++)
				(t[i][j] += res[i / 2][j + m]) %= p;
	}

	return t;
}

poly poly_composition(const poly& f, const poly& g) {
	int n = (int)f.size() - 1;

	poly a(n + 1);
	for (int i = 0; i <= n; i++)
		a[i] = f[n - i];
	
	vector<poly> b(n + 1);
	for (int i = 0; i <= n; i++)
		b[i] = {(p - g[i]) % p};
	
	vector<poly> t = bostan_mori_comp(n, a, b);

	poly res(n + 1);
	for (int i = 0; i <= n; i++)
		res[i] = t[i][0];
	return res;
}

bool not_prime[MAXN];
int prime[MAXN], prime_cnt, phi[MAXN];

void get_phi(int n) {
	not_prime[1] = true;
	phi[1] = 1;

	for (int i = 2; i <= n; i++) {
		if (!not_prime[i]) {
			prime[++prime_cnt] = i;
			phi[i] = i - 1;
		}

		for (int j = 1; j <= prime_cnt && i * prime[j] <= n; j++) {
			not_prime[i * prime[j]] = true;

			if (i % prime[j])
				phi[i * prime[j]] = phi[i] * (prime[j] - 1);
			else {
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
		}
	}
}

int fac[MAXN], fac_inv[MAXN];

void fac_init(int n) {
	fac[0] = fac_inv[0] = 1;
	for (int i = 1; i <= n; i++)
		fac[i] = (ll)fac[i - 1] * i % p;
	
	fac_inv[n] = qpow(fac[n], p - 2);
	for (int i = n - 1; i; i--)
		fac_inv[i] = (ll)fac_inv[i + 1] * (i + 1) % p;
}

// \sum_k c_i (1 + x) ^ k
poly calc(const poly& c, int n) {
	int m = (int)c.size() - 1;

	poly a(m + 1), b(m + 1);
	for (int i = 0; i <= m; i++) {
		a[i] = (ll)c[i] * fac[i] % p;
		b[i] = fac_inv[m - i];
	}

	poly t = poly_auto_mul(a, b);

	poly res(n + 1);
	for (int i = 0; i <= n && i <= m; i++)
		res[i] = (ll)t[m + i] * fac_inv[i] % p;
	
	return res;
}

poly polya_transform(const poly& f) {
	int n = (int)f.size() - 1;

	poly g(n + 1);
	g[0] = 1;
	for (int i = 1; i <= n; i++)
		g[i] = (p - f[i]) % p;
	
	g.resize(get_ntt_n(n + 1));
	g = poly_ln(g);
	g.resize(n + 1);

	poly res(n + 1);
	for (int k = 1; k <= n; k++) {
		int c = (ll)phi[k] * inv[k] % p;

		for (int i = 1; i * k <= n; i++)
			res[i * k] = (res[i * k] + (ll)g[i] * c) % p;
	}

	return res;
}

poly euler_transform(const poly& f) {
	int n = (int)f.size() - 1;

	poly a(n + 1);
	for (int k = 1; k <= n; k++)
		for (int i = 1; i * k <= n; i++)
			a[i * k] = (a[i * k] + (ll)f[i] * inv[k]) % p;
	
	a.resize(get_ntt_n(n + 1));
	a = poly_exp(a);
	a.resize(n + 1);

	return a;
}

int c[MAXN];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n, m;
	cin >> n >> m;
	
	int mx = 0;
	for (int i = 0; i < m; i++) {
		int x;
		cin >> x;

		c[x]++;
		mx = max(mx, x);
	}

	ntt_init(get_ntt_n(max(n, mx) * 2 + 1));
	fac_init(max(n, mx));
	get_phi(n);

	poly s1(mx), s2(mx);
	for (int i = 1; i <= mx; i++)
		s1[i - 1] = c[i];
	for (int i = 2; i <= mx; i++)
		s2[i - 2] = (ll)c[i] * (i - 1) % p;
	
	s1 = calc(s1, n);
	s2 = calc(s2, n);

	poly t(n + 1);
	t[0] = m;
	for (int i = 1; i <= n; i++)
		t[i] = s1[i - 1];
	
	t.resize(get_ntt_n(n + 1));
	t = poly_inv(t);
	t.resize(n + 1);
	for (int i = n; i; i--)
		t[i] = t[i - 1];
	t[0] = 0;

	poly f = poly_composite_inversion(t);

	t = s1;
	for (int i = 1; i <= n; i++)
		(t[i] += s2[i - 1]) %= p;
	t = poly_composition(t, f);

	poly g(n + 1);
	for (int i = 1; i <= n; i++)
		g[i] = t[i - 1];
	
	poly h = polya_transform(g);
	for (int i = 1; i <= n; i++)
		h[i] = ((f[i] - g[i] + p) % p - h[i] + p) % p;
	
	poly ans = euler_transform(h);
	for (int i = 1; i <= n; i++)
		cout << ans[i] << " \n"[i == n];

	return 0;
}
