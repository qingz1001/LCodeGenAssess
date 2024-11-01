#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main() {
    int N, H, Delta;
    scanf("%d %d %d", &N, &H, &Delta);

    // 定义一个二维数组来存储每棵树在每个高度上的柿子数量
    int **tree = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        tree[i] = (int *)malloc((H + 1) * sizeof(int));
        for (int j = 0; j <= H; j++) {
            tree[i][j] = 0;
        }
    }

    // 读取每棵树上柿子的分布情况
    for (int i = 0; i < N; i++) {
        int Ni;
        scanf("%d", &Ni);
        for (int j = 0; j < Ni; j++) {
            int height;
            scanf("%d", &height);
            tree[i][height]++;
        }
    }

    // 定义一个二维数组来存储到达每棵树每个高度时能吃到的最多柿子数量
    int **dp = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        dp[i] = (int *)malloc((H + 1) * sizeof(int));
        for (int j = 0; j <= H; j++) {
            dp[i][j] = 0;
        }
    }

    // 初始化dp数组，表示从阳台出发能吃到的柿子数量
    for (int i = 0; i < N; i++) {
        dp[i][0] = tree[i][0];
    }

    // 动态规划计算每棵树每个高度能吃到的最多柿子数量
    for (int h = 1; h <= H; h++) {
        for (int i = 0; i < N; i++) {
            int max = 0;
            // 计算从其他树跳到当前树的情况
            for (int j = 0; j < N; j++) {
                if (i != j) {
                    max = MAX(max, dp[j][h - Delta]);
                }
            }
            // 更新当前高度的最大值
            dp[i][h] = MAX(max + tree[i][h], dp[i][h - 1]);
        }
    }

    // 找到所有高度中能吃到的最多柿子数量
    int result = 0;
    for (int i = 0; i < N; i++) {
        result = MAX(result, dp[i][H]);
    }

    // 输出结果
    printf("%d\n", result);

    // 释放内存
    for (int i = 0; i < N; i++) {
        free(tree[i]);
        free(dp[i]);
    }
    free(tree);
    free(dp);

    return 0;
}