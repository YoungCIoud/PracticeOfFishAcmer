#include<bits/stdc++.h>

std::vector<int> get(std::string &s, int n) {
    std::vector<int> sa(n, 0), rk(n * 2, 0), tmp(n * 2, 0), cnt(n + 'z', 0);
    // init
    for (int i = 0; i < n; i++) {
        cnt[s[i]]++;
    }
    for (int i = 1; i <= 'z'; i++) {
        cnt[i] += cnt[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        sa[--cnt[s[i]]] = i;
    }
    rk[sa[0]] = 1;
    for (int i = 1, p = 1; i < n; i++) {
        rk[sa[i]] = (s[sa[i]] == s[sa[i - 1]] ? p : ++p);
    }

    // a -> b
    auto trans = [&](std::vector<int> &a, std::vector<int> &b, int d) -> void {
        std::fill(cnt.begin(), cnt.end(), 0);
        for (int i = 0; i < n; i++) {
            cnt[rk[i + d]]++;
        }
        for (int i = 1; i <= n; i++) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) {
            b[--cnt[rk[a[i] + d]]] = a[i];
        }
    };
    for (int k = 1; k < n; k <<= 1) {
        trans(sa, tmp, k), trans(tmp, sa, 0);

        tmp[sa[0]] = 1;
        for (int i = 1, p = 1; i < n; i++) {
            if (rk[sa[i]] > rk[sa[i - 1]] || rk[sa[i] + k] > rk[sa[i - 1] + k]) {
                p++;
            }
            tmp[sa[i]] = p;
        }
        rk = tmp;
    }
    return sa;
}

int main() {
    std::string s;
    std::cin >> s;
    for (auto i : get(s, s.length())) {
        std::cout << i + 1 << ' ';
    }
    std::cout << '\n';

    system("pause");
    return 0;
}