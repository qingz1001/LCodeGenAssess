#include <stdio.h>
#include <stdlib.h>

// 定义大臣结构体
typedef struct {
    int left;
    int right;
} Minister;

// 比较函数，用于qsort排序
int cmp(const void *a, const void *b) {
    Minister *ministerA = (Minister *)a;
    Minister *ministerB = (Minister *)b;
    if (ministerA->left == ministerB->left) {
        return ministerA->right - ministerB->right;
    }
    return ministerA->left - ministerB->left;
}

int main() {
    int n;
    scanf("%d", &n);
    Minister ministers[n + 1]; // 加上国王

    // 输入国王和大臣的数据
    ministers[0].left = 1; // 国王左手的数设为1，方便计算
    ministers[0].right = 1; // 国王右手的数设为1，方便计算
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &ministers[i].left, &ministers[i].right);
    }

    // 对大臣进行排序
    qsort(ministers + 1, n, sizeof(Minister), cmp);

    // 计算每个大臣获得的金币数
    long long product = 1;
    int max_coins = 0;
    for (int i = 1; i <= n; i++) {
        product *= ministers[i - 1].left;
        int coins = product / ministers[i].right;
        if (coins > max_coins) {
            max_coins = coins;
        }
    }

    // 输出结果
    printf("%d\n", max_coins);
    return 0;
}