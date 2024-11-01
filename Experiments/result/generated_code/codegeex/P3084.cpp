#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
using namespace std;

#define MAXN 200010
#define MAXM 100010

struct Interval {
    int l, r;
} intervals[MAXM];

int n, m, ans, dp[MAXN], maxn[MAXN];

bool cmp(const Interval &a, const Interval &b) {
    return a.r < b.r;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &intervals[i].l, &intervals[i].r);
    }
    
    // 按照右端点进行排序
    sort(intervals + 1, intervals + m + 1, cmp);
    
    // 动态规划求解
    for (int i = 1; i <= m; i++) {
        // 查找第一个右端点小于等于当前区间左端点的区间
        int k = lower_bound(intervals + 1, intervals + i, (Interval){0, intervals[i].l - 1}) - intervals;
        
        // 如果没有找到这样的区间，说明无解
        if (k == 0) {
            printf("-1\n");
            return 0;
        }
        
        // 更新dp数组
        dp[i] = dp[k - 1] + 1;
        maxn[i] = max(maxn[i - 1], dp[i]);
    }
    
    // 找到最大值
    ans = maxn[m];
    
    // 检查是否所有区间都满足条件
    for (int i = 1; i <= m; i++) {
        if (dp[i] == intervals[i].r - intervals[i].l + 1) {
            ans--;
        }
    }
    
    printf("%d\n", ans);
    return 0;
}