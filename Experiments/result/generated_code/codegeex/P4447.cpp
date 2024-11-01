#include <stdio.h>
#include <stdlib.h>

// 定义全局变量
int n;
int a[100005];
int f[100005];
int b[100005];
int cnt;

// 比较函数，用于排序
int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

// 查找x在b数组中的位置
int find(int x) {
    int l = 1, r = cnt;
    while (l < r) {
        int mid = (l + r) / 2;
        if (b[mid] < x) l = mid + 1;
        else r = mid;
    }
    return l;
}

int main() {
    // 读取输入
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

    // 对实力值进行排序
    qsort(a + 1, n, sizeof(int), cmp);

    // 去重并存储到b数组中
    b[cnt = 1] = a[1];
    for (int i = 2; i <= n; i++) {
        if (a[i] != a[i - 1]) b[++cnt] = a[i];
    }

    // 初始化f数组
    for (int i = 1; i <= cnt; i++) f[i] = 1;

    // 动态规划求解最长连续子序列
    for (int i = 2; i <= cnt; i++) {
        int j = find(a[i] - 1);
        if (j != 0) f[i] = f[j] + 1;
    }

    // 找到人数最少的组的人数最大值
    int minGroupSize = 1000000;
    for (int i = 1; i <= cnt; i++) {
        if (f[i] < minGroupSize) minGroupSize = f[i];
    }

    // 输出结果
    printf("%d\n", minGroupSize);
    return 0;
}