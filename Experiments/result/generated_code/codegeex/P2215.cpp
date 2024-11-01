#include <stdio.h>
#include <stdlib.h>

// 定义全局变量
int n, m, a[10005], dp[10005], pre[10005], ans[10005];

// 比较函数，用于qsort排序
int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

// 打印上升序列
void print(int pos) {
    if (pos == 0) {
        for (int i = 1; i <= ans[0]; i++) {
            printf("%d ", ans[i]);
        }
        printf("\n");
        return;
    }
    print(pre[pos]);
    printf("%d ", a[pos]);
}

int main() {
    // 读取序列长度
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    // 对序列进行排序
    qsort(a + 1, n, sizeof(int), cmp);

    // 初始化dp数组
    dp[0] = 0;
    dp[1] = 1;
    pre[1] = 0;

    // 动态规划求解最长上升子序列
    for (int i = 2; i <= n; i++) {
        dp[i] = 1;
        for (int j = 1; j < i; j++) {
            if (a[j] < a[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                pre[i] = j;
            }
        }
    }

    // 找到最长上升子序列的长度和位置
    int maxlen = 0, maxpos = 0;
    for (int i = 1; i <= n; i++) {
        if (dp[i] > maxlen) {
            maxlen = dp[i];
            maxpos = i;
        }
    }

    // 读取询问次数
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        int L;
        scanf("%d", &L);

        // 如果询问的长度大于最长上升子序列的长度，则输出Impossible
        if (L > maxlen) {
            printf("Impossible\n");
            continue;
        }

        // 反向构建长度为L的上升子序列
        int pos = maxpos;
        for (int j = maxlen; j >= L; j--) {
            while (dp[pos] != j) {
                pos = pre[pos];
            }
            ans[j] = a[pos];
            pos = pre[pos];
        }

        // 打印结果
        ans[0] = L;
        print(L);
    }

    return 0;
}