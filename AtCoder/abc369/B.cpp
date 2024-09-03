#include<bits/stdc++.h>

int main()
{
    int n = 0;
    std::cin >> n;

    std::vector L(0, 0), R(0, 0);
    for (int i = 0; i < n; i++)
    {
        int a = 0;
        char c = 0;
        std::cin >> a >> c;

        if (c == 'L') L.push_back(a);
        else R.push_back(a);
    }

    int ans = 0;
    for (int i = 1; i < L.size(); i++)
        ans += abs(L[i] - L[i - 1]);
    for (int i = 1; i < R.size(); i++)
        ans += abs(R[i] - R[i - 1]);
    std::cout << ans << '\n';


    system("pause");

    return 0;
}