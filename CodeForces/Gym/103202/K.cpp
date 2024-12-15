#include<bits/stdc++.h>

int main() {
    int n = 0;
    std::cin >> n;
    std::map<int, std::array<int, 2>> cnt;

    int TP = 0, FN = 0, FP = 0, TN = 0;
    for (int i = 0; i < n; i++) {
        char c = 0;
        int a = 0;
        std::cin >> c >> a;
        cnt[a][c == '+']++;

        if (c == '+') {
            FN++;
        }
        else {
            TN++;
        }
    }
    // 0: FPR, 1: TPR
    std::vector val(1, std::array<double, 2>{ 0.0, 0.0 });
    for (auto it = cnt.rbegin(); it != cnt.rend(); it++) {
        auto &[tmp, cnt_sig] = *it;
        auto &[N, P] = cnt_sig;

        TN -= N, FN -= P;
        TP += P, FP += N;
        double FPR = (1.0 * FP) / (1.0 * (TN + FP));
        double TPR = (1.0 * TP) / (1.0 * (TP + FN));
        if (FPR == val.back()[0]) {
            val.back()[1] = std::max(val.back()[1], TPR);
        }
        else {
            val.push_back({ FPR, TPR });
        }
    }

    // for (auto &[F, T] : val) {
    //     std::cout << F << '\t';
    // }
    // std::cout << '\n';
    // for (auto &[F, T] : val) {
    //     std::cout << T << '\t';
    // }
    // std::cout << '\n';

    double ans = 0;
    for (int i = 1; i < val.size(); i++) {
        double l = val[i - 1][0], r = val[i][0], h = val[i - 1][1];
        ans += (r - l) * h;
    }
    std::cout << std::fixed << std::setprecision(15) << ans << '\n';

    system("pause");
    return 0;
}