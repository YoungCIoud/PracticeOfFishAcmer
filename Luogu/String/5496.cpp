#include <bits/stdc++.h>

constexpr int N = 5e5;

std::string s;
int tr[N + 5][26];
int fail[N + 5], len[N + 5];
int deep[N + 5];

int getfail(int u, int i) {
	while (i - len[u] - 1 < 0 || s[i - len[u] - 1] != s[i]) {
		u = fail[u];
	}
	return u;
}
int main () {
	fail[0] = 1;
	len[1] = -1;
	std::cin >> s;
	int ans = 0;
	for (int i = 0, now = 0, tot = 1; i < s.length(); i++) {
		int c = (s[i] - 'a' + ans) % 26;
		s[i] = c + 'a';
		int pos = getfail(now, i);
		if (tr[pos][c] == 0) {
			tot++;
			fail[tot] = tr[getfail(fail[pos], i)][c];
			tr[pos][c] = tot, len[tot] = len[pos] + 2, deep[tot] = deep[fail[tot]] + 1;
		}
		now = tr[pos][c];
		ans = deep[now];
		std::cout << ans << ' ';
	}
	// system("pause");
	return 0;
}
