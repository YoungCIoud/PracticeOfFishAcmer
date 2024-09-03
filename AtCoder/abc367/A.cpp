#include<bits/stdc++.h>

bool solve()
{
    int a = 0,b = 0, c = 0;
    std::cin >> a >> b >> c;
    if (b <= c) return a < b || c < a;
    else return c < a && a < b;
}

int main()
{
    std::cout << (solve() ? "Yes" : "No");
    
    system("pause");
    return 0;
}