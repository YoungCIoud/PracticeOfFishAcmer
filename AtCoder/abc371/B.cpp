#include<bits/stdc++.h>

constexpr int N = 100;

bool vis[N + 5];
int main()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    while (m--)
    {
        int a = 0;
        char c = 0;
        std::cin >> a >> c;
        if (vis[a] || c == 'F') puts("No");
        else
        {
            puts("Yes");
            vis[a] = true;
        }
    }
    return 0;
}