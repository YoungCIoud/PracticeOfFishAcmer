#include<bits/stdc++.h>

int n, k;
int R[15];
std::vector<int> ans;

void dfs(int dep, int sum = 0)
{
    if (dep == n)
    {
        if (sum % k == 0)
        {
            for (auto& i : ans) std::cout << i << ' ';
            std::cout << '\n';
        }
        
        return;
    }

    for (int i = 1; i <= R[dep]; i++)
    {
        ans.push_back(i);
        dfs(dep + 1, sum + i);
        ans.pop_back();
    }
    
    return;
}

int main()
{
    std::cin >> n >> k;
    for (int i = 0; i < n; i++)
        std::cin >> R[i];

    dfs(0);

    system("pause");
    return 0;
}