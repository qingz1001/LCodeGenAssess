#include <stdio.h>
#include <stdlib.h>

#define MAXN 1001

int n, q;
int a[MAXN][MAXN];
int sorted_a[MAXN * MAXN];
int cnt[MAXN * MAXN];

int cmp(const void *a, const void *b) {
    return *(int *)b - *(int *)a;
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
            sorted_a[i * n + j] = a[i][j];
        }
    }

    // 对每一行进行排序
    for (int i = 0; i < n; i++) {
        qsort(sorted_a + i * n, n, sizeof(int), cmp);
    }

    // 计算每个值出现的次数
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cnt[sorted_a[i * n + j]]++;
        }
    }

    // 计算前缀和
    for (int i = 1; i <= n * n; i++) {
        cnt[i] += cnt[i - 1];
    }

    // 处理每个查询
    for (int i = 0; i < q; i++) {
        int v;
        scanf("%d", &v);
        printf("%d\n", cnt[v]);
    }

    return 0;
}