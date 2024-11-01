#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef long long ll;

// 定义矿石结构体
typedef struct {
    int weight;
    int value;
} Ore;

// 定义区间结构体
typedef struct {
    int left;
    int right;
} Interval;

// 比较函数，用于排序矿石
int compare(const void *a, const void *b) {
    Ore *oreA = (Ore *)a;
    Ore *oreB = (Ore *)b;
    return oreA->weight - oreB->weight;
}

// 计算前缀和
void calculatePrefixSums(int n, Ore *ores, int *prefixWeights, int *prefixValues) {
    prefixWeights[0] = 0;
    prefixValues[0] = 0;
    for (int i = 1; i <= n; i++) {
        prefixWeights[i] = prefixWeights[i - 1] + (ores[i - 1].weight >= W ? 1 : 0);
        prefixValues[i] = prefixValues[i - 1] + (ores[i - 1].weight >= W ? ores[i - 1].value : 0);
    }
}

// 计算区间检验值
ll calculateIntervalValue(int left, int right, int *prefixWeights, int *prefixValues) {
    return (ll)(prefixWeights[right] - prefixWeights[left - 1]) * (ll)(prefixValues[right] - prefixValues[left - 1]);
}

int main() {
    int n, m;
    ll s;
    scanf("%d %d %lld", &n, &m, &s);

    Ore *ores = (Ore *)malloc(n * sizeof(Ore));
    Interval *intervals = (Interval *)malloc(m * sizeof(Interval));

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &ores[i].weight, &ores[i].value);
    }

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &intervals[i].left, &intervals[i].right);
    }

    // 对矿石按重量排序
    qsort(ores, n, sizeof(Ore), compare);

    // 前缀和数组
    int *prefixWeights = (int *)malloc((n + 1) * sizeof(int));
    int *prefixValues = (int *)malloc((n + 1) * sizeof(int));

    // 二分查找的左右边界
    int left = 0, right = 1000000;
    ll minDiff = LLONG_MAX;

    while (left <= right) {
        int mid = (left + right) / 2;
        W = mid;

        // 计算前缀和
        calculatePrefixSums(n, ores, prefixWeights, prefixValues);

        ll totalValue = 0;
        for (int i = 0; i < m; i++) {
            totalValue += calculateIntervalValue(intervals[i].left, intervals[i].right, prefixWeights, prefixValues);
        }

        ll diff = abs(s - totalValue);
        if (diff < minDiff) {
            minDiff = diff;
        }

        if (totalValue < s) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    printf("%lld\n", minDiff);

    free(ores);
    free(intervals);
    free(prefixWeights);
    free(prefixValues);

    return 0;
}