## 对顶堆

对顶堆由一个大根堆和小根堆组成, 能够**动态**维护第k大的值或中位数.

对顶堆能够由优先队列或着多重集实现, 只不过后者能够更方便的进行删除元素.

下面给出维护中位数的例子:
```cpp
class mset
{
public:
    // 初始时插入正负无穷
    void init()
    {
        less.clear(), greater.clear();
        less.insert(-Inf), greater.insert(Inf);
        less_sum = 0, greater_sum = 0;
    }
    void insert(int val)
    {
        if (val < *greater.begin()) less.insert(val), less_sum += val;
        else greater.insert(val), greater_sum += val;

        adjust(); 
    }
    void erase(int val)
    {
        if (val < *greater.begin()) less.erase(less.lower_bound(val)), less_sum -= val;
        else greater.erase(greater.lower_bound(val)), greater_sum -= val;

        adjust();
    }
    int get()
    {
        // 求中位数要考虑元素总个数的奇偶
        int m = 0;
        int d = less.size() - greater.size();

        if (d)
            m = *less.begin();
        else
            m = *less.begin() + *greater.begin() >> 1;
        
        return m;
    }
private:
    std::multiset<int, std::greater<int>> less;
    std::multiset<int> greater;
    i64 less_sum, greater_sum; // 根据题目要求而加

    void adjust()
    {
        while (greater.size() > less.size())
        {
            auto it = greater.begin();
            less.insert(*it);
            less_sum += *it;

            greater_sum -= *it;
            greater.erase(it);
        }
        while (less.size() > greater.size() + 1)
        {
            auto it = less.begin();
            greater.insert(*it);
            greater_sum += *it;

            less_sum -= *it;
            less.erase(less.begin());
        }
    }
};
```