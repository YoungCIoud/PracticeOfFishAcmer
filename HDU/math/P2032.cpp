#include<bits/stdc++.h>
int c[30][30];

int main()
{
    c[0][0] = 1;
    for (int i = 1; i < 30; i++)
    {
        c[i][0] = 1;
        for (int j = 1; j <= i; j++)
            c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
    }

    int n = 0;
    while (std::cin >> n)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j <= i; j++)
                std::cout << c[i][j] << " \n"[j == i];
        std::cout << '\n';
    }
}