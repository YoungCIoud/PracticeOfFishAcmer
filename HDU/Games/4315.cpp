#include <iostream>
#include <vector>
#include <algorithm>

int main () {
    int n = 0, k = 0;
    while (std::cin >> n >> k) {
        std::vector<int> p(n, 0);
        for (int i = 0; i < n; i++) {
            std::cin >> p[i];
            p[i] = -p[i];
        }
        if (k == 1) {
            std::cout << "Alice\n";
            continue;
        }
        std::sort(p.begin(), p.end());
        int ans = 0;
        for (int i = 1; i < n; i += 2) {
            ans ^= (p[i] - p[i - 1] - 1);
        }
        if (n & 1) {
            ans ^= -p.back() - (k == 2);
        }

        std::cout << (ans == 0 ? "Bob" : "Alice") << "\n";
    }
    // system("pause");
    return 0;
}