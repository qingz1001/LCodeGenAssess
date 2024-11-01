#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, H, Delta;
    scanf("%d %d %d", &N, &H, &Delta);

    // 创建一个二维数组来存储每棵树上每个高度的柿子数量
    int **tree = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        tree[i] = (int *)malloc(H * sizeof(int));
        for (int j = 0; j < H; j++) {
            tree[i][j] = 0;
        }
    }

    // 读取每棵树上的柿子数量和高度
    for (int i = 0; i < N; i++) {
        int Ni;
        scanf("%d", &Ni);
        for (int j = 0; j < Ni; j++) {
            int Ti;
            scanf("%d", &Ti);
            tree[i][Ti - 1]++;
        }
    }

    // 创建一个二维数组来存储小猫在不同高度和不同树上的最大柿子数
    int **dp = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        dp[i] = (int *)malloc((H + Delta) * sizeof(int));
        for (int j = 0; j < H + Delta; j++) {
            dp[i][j] = 0;
        }
    }

    // 动态规划计算小猫在不同高度和不同树上的最大柿子数
    for (int height = 0; height < H + Delta; height++) {
        for (int tree_index = 0; tree_index < N; tree_index++) {
            if (height < H) {
                dp[tree_index][height] = tree[tree_index][height];
            }
            if (height >= Delta) {
                for (int j = 0; j < N; j++) {
                    dp[tree_index][height] = 
                        (dp[tree_index][height] > dp[j][height - Delta] + tree[tree_index][height]) ? 
                        dp[tree_index][height] : dp[j][height - Delta] + tree[tree_index][height];
                }
            }
        }
    }

    // 找到小猫在不同高度和不同树上的最大柿子数
    int max_persimmons = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < H + Delta; j++) {
            if (dp[i][j] > max_persimmons) {
                max_persimmons = dp[i][j];
            }
        }
    }

    // 输出结果
    printf("%d\n", max_persimmons);

    // 释放内存
    for (int i = 0; i < N; i++) {
        free(tree[i]);
        free(dp[i]);
    }
    free(tree);
    free(dp);

    return 0;
}