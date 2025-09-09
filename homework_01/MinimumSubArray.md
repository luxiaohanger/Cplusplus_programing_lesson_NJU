# MinimumSubArray最短子数组
给定一个含有 n 个正整数的数组和一个正整数 target 。

找出该数组中满足其总和大于等于 target 的长度最小的 子数组

{nums[l], nums[l+1], ..., nums[r-1],nums[r]} ，并分别返回该子数组的左右下标之和（l+r)。如果存在不止一个这样的子数组，返回最小左右下标和。如果不存在符合条件的子数组，返回 0 。
（如果数组长度为1，则返回此下标）
## 输入描述
正整数个数n,正整数数组nums,目标正整数target。

## 输出描述
满足条件的子数组左右下标和;如果不存在符合条件的子数组，返回0

### 提示
1.可以构造可供二分查找的数组解决这个问题吗？

2.左下标变化的时机可不可以优化？

解决以上其中一点就可以拿到全部分数。

## 总结
1.写否定判断时，很可能把边界条件漏检验
```c++
if(index[1]!=0)right=mid;
//index[1]==0时也有可能找到了，例如arr[0]
```
2.有关连续和的问题可以用前缀和求Sn,再利用Sn-Si求连续和  

3.二分查找对于退出要思考清楚，由于index是退出前更新，退出时index可能是不成立状态，没有正确数据，因此退出后再次获取正确index输出  
4.**关于二分查找的形式**
[l, r] 始终是「答案闭区间」，用 l!=r 或 l<r 都行
```c++
int mid = l + (r - l) / 2;
//最稳妥的写法，既不会溢出，也不会像l/2+r/2导致奇数时偏差
```
## 滑动窗口
考虑到所有数全是正数，因此只要增加原有数组左右两端，就是递增的  
可以考虑使用两个“指针”维护一个连续的窗口，通过移动窗口覆盖所有可能的子数组  

**如果当前数组满足条件，则右加一位一定可以，再收缩左侧指针  
遍历：当前位置的右指针所有可能近的左指针**  

以此类推，可以***保证我们遍历了所有可能小的窗口***，通过维护一个len和r+l,就可以得出答案  
这是一个O(n)的方法，二分O(nlogn)适用于正负数都有的情况
```c++
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];
    int target;
    cin >> target;

    int left = 0, sum = 0;
    int minLen = n + 1;   // 记录最短长度，使用不可能的数以避免冲突
    int res = 0;          // 记录答案 (l+r)

    for (int right = 0; right < n; right++) {
        sum += nums[right];//这一步我们找到了右指针最近也必须在这里
        while (sum >= target) {
        //确保窗口正确性
            int len = right - left + 1;
            if (len < minLen) {
                minLen = len;
                res = left + right;
            } else if (len == minLen) {
                res = min(res, left + right); // 取最小 l+r
            }
            sum -= nums[left++];//减少长度，试探更短的
        }
    }

    if (minLen == n + 1) {
        cout << 0;  // 没有子数组符合
    } else if (minLen == 1) {
        cout << res / 2;  // 长度=1时，res=l+r=2*l，需要输出 l
    } else {
        cout << res;      // 其他情况输出 l+r
    }

    return 0;
}

```
