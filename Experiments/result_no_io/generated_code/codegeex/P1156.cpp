#include <stdio.h>
#include <string.h>

#define MAX_GARBAGE 101
#define MAX_TIME 1001
#define MAX_HEIGHT 101

int dp[MAX_TIME][MAX_HEIGHT];
int garbage[MAX_GARBAGE][3];

int main() {
    int D, G;
    scanf("%d %d", &D, &G);

    for (int i = 0; i < G; i++) {
        scanf("%d %d %d", &garbage[i][0], &garbage[i][1], &garbage[i][2]);
    }

    memset(dp, -1, sizeof(dp));
    dp[10][0] = 10; // 初始状态，卡门有10小时的能量

    for (int i = 0; i < G; i++) {
        for (int j = MAX_TIME - 1; j >= 10; j--) { // 从后向前遍历时间，避免覆盖之前的计算结果
            for (int k = MAX_HEIGHT - 1; k >= 0; k--) {
                if (dp[j][k] != -1) {
                    // 堆放垃圾
                    if (k + garbage[i][2] < MAX_HEIGHT) {
                        dp[j][k + garbage[i][2]] = dp[j][k];
                    }
                    // 吃垃圾
                    if (j + garbage[i][1] < MAX_TIME) {
                        dp[j + garbage[i][1]][k] = dp[j][k];
                    }
                }
            }
        }
    }

    for (int i = 0; i < MAX_TIME; i++) {
        for (int j = 0; j < MAX_HEIGHT; j++) {
            if (dp[i][j] != -1 && j >= D) {
                printf("%d\n", i);
                return 0;
            }
        }
    }

    for (int i = MAX_TIME - 1; i >= 0; i--) {
        for (int j = 0; j < MAX_HEIGHT; j++) {
            if (dp[i][j] != -1) {
                printf("%d\n", i);
                return 0;
            }
        }
    }

    printf("0\n");
    return 0;
}