#include<bits/stdc++.h>

int main()
{
    int a = 0, b = 0, ans = 0;
    std::cin >> a >> b;

    if (a == b) ans = 1;
    else if ((a + b) & 1) ans = 2;
    else ans = 3;
    std::cout << ans << '\n';

    system("pause");

    return 0;
}