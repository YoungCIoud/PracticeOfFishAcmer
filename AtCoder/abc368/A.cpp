#include<bits/stdc++.h>

int main()
{
    int n = 0, k = 0;
    std::cin >> n >> k;
    k = n - k;
    std::vector<int> a(n);
    for (int &i : a) std::cin >> i;
    for (int i = k; i < n; i++) std::cout << a[i] << " ";
    for (int i = 0; i < k; i++) std::cout << a[i] << " ";

    system("pause");

    return 0;
}