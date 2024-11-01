#include <stdio.h>
#include <stdlib.h>

// 定义大臣结构体
typedef struct {
    int left;
    int right;
} Minister;

// 比较函数，用于qsort排序
int compare(const void *a, const void *b) {
    Minister *ministerA = (Minister *)a;
    Minister *ministerB = (Minister *)b;
    return ministerA->right - ministerB->right;
}

int main() {
    int n;
    scanf("%d", &n);

    Minister ministers[n + 1];
    ministers[0].left = 1; // 国王左手上的数
    ministers[0].right = 1; // 国王右手上的数

    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &ministers[i].left, &ministers[i].right);
    }

    // 按照大臣右手上的数从小到大排序
    qsort(ministers + 1, n, sizeof(Minister), compare);

    // 计算每个大臣获得的金币数
    long long product = ministers[0].left; // 初始乘积为国王左手上的数
    int max_coins = 0;

    for (int i = 1; i <= n; i++) {
        int coins = product / ministers[i].right;
        if (coins > max_coins) {
            max_coins = coins;
        }
        product *= ministers[i].left;
    }

    printf("%d\n", max_coins);

    return 0;
}