// 树状数组 lq的码
#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;
 
#define endl '\n'
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define iter(x) x.begin(),x.end()
// #define int long long
// #define double long double
 
const int md = 1e9+7;
const int maxN = 1e4+5;
 
struct BinaryIndexTree
{
    int m_size;
    vector<int> arr;
 
    void init(int n) {
        m_size = n;
        arr.assign(n,0);
    }
 
    inline int lowBit(int num) {
        return num & (-num);
    }
 
    //单点修改
    void update(int index, int value) {
        index += 1;
        for (int i = index; i <= m_size; i += lowBit(i))
            arr[i] += value;
    }
 
    //求前n项和
    int sum(int n) {
        n += 1;
        int ans = 0;
        //到i的时候还能进行一次运算，之后就不行了，i=1的时候为最小
        for (int i = n; i; i -= lowBit(i))
            ans += arr[i];
        //n为0的时候返回0, arr的第0位也为0
        return ans;
    }
 
    //求区间和
    int sum(int left, int right) {
        return sum(right) - sum(left-1);
    }
} tr[21];
 
void modify(int num, int var) {
    for (int i = 0; i <= 20; ++i) {
        int p = 1 << i+1;
        tr[i].update((-num % p + p) % p, var);
    }
}
 
signed main()
{
    IOS;
    for (int i = 0; i <= 20; ++i) {
        tr[i].init(1 << i + 1);
    }
     
    int q, cur = 0;
    cin >> q;
 
    vector<int> pre(q+5,0);
 
    while (q--) {
 
        int t, x;
        cin >> t >> x;
 
        while (t--) {
            modify(pre[cur-1],-1);
            cur -= 1;
        }
 
        pre[cur+1] = pre[cur] + x;
        cur += 1;
 
        modify(pre[cur-1],1);
 
        int ans = 0;
        for (int i = 0; i <= 20; ++i) {
            int p = 1 << i+1;
            int l = 1 << i;
            int r = p-1;
 
            l = (l - pre[cur] % p + p) % p;
            r = (r - pre[cur] % p + p) % p;
 
            int cnt = 0;
 
            if (l <= r) {
                cnt = tr[i].sum(l,r);
            }
            else {
                cnt = tr[i].sum(0,r) + tr[i].sum(l,p-1);
            }
            ans |= (cnt & 1 ? 1 << i : 0);
        }
 
        cout << ans << endl;
 
    }
 
    system("pause");
    return 0;
}
