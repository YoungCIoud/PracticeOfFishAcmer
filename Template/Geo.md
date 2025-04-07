## 二维向量
```cpp
// 二维向量
class v2
{
public:
    v2(int x = 0, int y = 0):x(x), y(y)
    {
        len = sqrt(x * x + y * y);
    }
    // 向量由a指向b
    v2(std::array<int, 2>& a, std::array<int, 2>& b)
    {
        x = b[0] - a[0], y = b[1] - a[1];
        len = sqrt(x * x + y * y);
    }
    
    double length()
    {
        return len;
    }

    v2 operator+(const v2& a)
    {
        return v2(x + a.x, y + a.y);
    }

    v2 operator-(const v2& a)
    {
        return v2(x - a.x, y - a.y);
    }
    // 数乘
    v2 operator* (const int a)
    {
        return v2(a * x, a * y);
    }
    // 点积
    int operator* (const v2& a)
    {
        return x * a.x + y * a.y;
    }
    // 叉积
    int operator^ (const v2& a)
    {
        return x * a.y - a.x * y;
    }
private:
    int x, y;
    double len;
};
```

## 点集的凸包
```c++
int main()
{
    int n = 0;
    std::cin >> n;
    std::vector<std::array<double, 2>> a(n);
    for (auto& [x, y] : a) std::cin >> x >> y;
    sort(a.begin(), a.end());

    // 凸包上的点从排好序后的0号点开始按逆时针的顺序存放在c中
    // c中第一个元素和最后一个元素都是0号点
    std::vector<int> stk(n), c;
    int p = -1;
    for (int i = 0; i < n; i++)
    {
        // ^被重载为二维向量叉积的运算符
        while (p >= 1 && (v2(a[stk[p - 1]], a[stk[p]]) ^ v2(a[stk[p]], a[i])) > 0) p--;
        stk[++p] = i;
    }
    for (int i = 0; i <= p; i++) c.push_back(stk[i]);

    p = -1;
    for (int i = n - 1; i >= 0; i--)
    {
        while (p >= 1 && (v2(a[stk[p - 1]], a[stk[p]]) ^ v2(a[stk[p]], a[i])) > 0) p--;
        stk[++p] = i;
    }
    for (int i = 1; i <= p; i++) c.push_back(stk[i]);

    auto dis = [&](std::array<double, 2> a, std::array<double, 2> b) -> double
    {
        return sqrt((a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]));
    }; 

    double ans = 0.0;
    for (int i = 1; i < c.size(); i++)
        ans += dis(a[c[i]], a[c[i - 1]]);
    
    printf("%.2lf\n", ans);
    
    system("pause");

    return 0;
}
```

## 极角排序

**极角定义**  
在平面上任取一个顶点$O$，称为极点；作射线$OX$，那么$OX$就是极轴。平面上任意一点和$O$点作向量，与$OX$形成的夹角就叫做极角。通常选定逆时针方向为正，一般我们以$x$轴为极轴，那么极角就是平面向量与$x$轴的夹角

**极角排序**  
给定极轴, 将平面上的点按照极角的大小排序就叫极角排序.  
当极角相当时, 按长度排序.


```cpp
// 版本1
// O是极点
inline bool cmp(Node &A, Node &B)
{
    std::pair<int, int> OA = { A.x - O.x, A.y - O.y }, OB = { B.x - O.x, B.y - O.y };
    if (OA ^ OB) return (OA ^ OB) > 0;
    else return OA.first < OB.first;
}
```
```cpp
// 版本2
inline bool cmp(Node &A, Node &B)
{
    // 考虑向量和OP同向
    if (A.y == O.y && A.x >= O.x) return true;
    if (B.y == O.y && B.x >= O.x) return false;

    std::pair<int, int> OP = { 1, 0 }, OA = { A.x - O.x, A.y - O.y }, OB = { B.x - O.x, B.y - O.y };
    // 考虑OA和OB在OP异侧
    if (((OP ^ OA) > 0) ^ ((OP ^ OB) > 0)) return (OP ^ OA) > 0;
    else return (OA ^ OB) > 0;
}
```

**例题** [Almost Convex](https://codeforces.com/gym/104901/problem/M)

## 求多边形面积
```cpp
double get() {
    double S = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        S += (a[i].x * a[j].y - a[j].x * a[i].y);
    }
    return S / 2.0
}
```

## 最小增量法求最小圆覆盖
```cpp
void solve() {
    // code ...

    // 将读入的点集重新排列
    // 防止被特定的数据卡
    std::random_shuffle(a, a + n);
    
    // 对于一个点，最小圆就是半径为 0 的。
    point O = a[0];
    double r = 0;
    // 逐步加入第 i 个点
    for (int i = 1; i < n; i++) {
        // 在圆就不变
        if (dis2(O, a[i]) - r <= EPS) {
            continue;
        }

        // 不在就重新确定圆
        O = a[i], r = 0;
        for (int j = 0; j < i; j++) {
            if (dis2(O, a[j]) - r <= EPS) {
                continue;
            }
            // 由两个点确定的最小圆
            O = cen(a[i], a[j]), r = dis2(O, a[j]);
            for (int k = 0; k < j; k++) {
                if (dis2(O, a[k]) - r <= EPS) {
                    continue;
                }
                // 由三个点确定的最小圆
                O = cen(a[i], a[j], a[k]), r = dis2(O, a[i]);
            }
        }
    }

    // code ...
}
```