#include<bits/stdc++.h>

int main()
{
    std::string s;
    std::cin >> s;

    while (s.back() == '0') s.pop_back();
    if (s.back() == '.') s.pop_back();
    std::cout << s << '\n';
    
    system("pause");
    return 0;
}