#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_M 100

int N, M;
int a[MAX_N]; // 大葱的体积
int b[MAX_M]; // 抽屉的容积
int w[MAX_N][MAX_M]; // 神力矩阵
int result[MAX_N]; // 结果数组，记录每棵大葱被放到哪个抽屉

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    FILE *input = fopen("drawer1.in", "r");
    FILE *output = fopen("drawer1.out", "w");

    fscanf(input, "%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        fscanf(input, "%d", &a[i]);
    }
    for (int j = 0; j < M; j++) {
        fscanf(input, "%d", &b[j]);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            fscanf(input, "%d", &w[i][j]);
        }
    }

    // 贪心算法：每次选择能产生最大神力的抽屉
    for (int i = 0; i < N; i++) {
        int max_power = -1;
        int best_drawer = -1;
        for (int j = 0; j < M; j++) {
            if (a[i] <= b[j] && w[i][j] > max_power) {
                max_power = w[i][j];
                best_drawer = j + 1; // 抽屉编号从1开始
            }
        }
        if (best_drawer != -1) {
            result[i] = best_drawer;
            b[best_drawer - 1] -= a[i]; // 更新抽屉的剩余容积
        } else {
            result[i] = 0; // 没有合适的抽屉
        }
    }

    // 输出结果
    for (int i = 0; i < N; i++) {
        fprintf(output, "%d\n", result[i]);
    }

    fclose(input);
    fclose(output);
    return 0;
}