#include<bits/stdc++.h>

int main()
{
    char a, b, c;
    std::cin >> a >> b >> c;
    if (a ^ b) puts("A");
    else if (b ^ c) puts("C");
    else puts("B");
    return 0;
}