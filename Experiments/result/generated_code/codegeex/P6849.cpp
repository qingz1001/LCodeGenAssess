#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_M 100

int main() {
    int N, M;
    int a[MAX_N], b[MAX_M];
    int w[MAX_N][MAX_M];
    int result[MAX_N];

    // 读取输入
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }
    for (int j = 0; j < M; j++) {
        scanf("%d", &b[j]);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &w[i][j]);
        }
    }

    // 初始化结果数组
    for (int i = 0; i < N; i++) {
        result[i] = 0;
    }

    // 处理每个大葱
    for (int i = 0; i < N; i++) {
        int max_power = 0;
        int best_drawer = -1;

        // 找到当前大葱放到哪个抽屉可以获得最大神力
        for (int j = 0; j < M; j++) {
            if (a[i] <= b[j] && w[i][j] > max_power) {
                max_power = w[i][j];
                best_drawer = j + 1; // 记录抽屉编号，抽屉编号从1开始
            }
        }

        // 更新结果
        result[i] = best_drawer;
    }

    // 输出结果
    for (int i = 0; i < N; i++) {
        printf("%d\n", result[i]);
    }

    return 0;
}