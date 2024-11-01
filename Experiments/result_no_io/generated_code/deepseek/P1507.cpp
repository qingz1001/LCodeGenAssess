#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_H 400
#define MAX_T 400
#define MAX_N 50

typedef struct {
    int h; // 体积
    int t; // 质量
    int k; // 卡路里
} Food;

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int h, t, n;
    scanf("%d %d", &h, &t);
    scanf("%d", &n);

    Food foods[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &foods[i].h, &foods[i].t, &foods[i].k);
    }

    int dp[MAX_H + 1][MAX_T + 1];
    memset(dp, 0, sizeof(dp));

    for (int i = 0; i < n; i++) {
        for (int j = h; j >= foods[i].h; j--) {
            for (int k = t; k >= foods[i].t; k--) {
                dp[j][k] = max(dp[j][k], dp[j - foods[i].h][k - foods[i].t] + foods[i].k);
            }
        }
    }

    printf("%d\n", dp[h][t]);

    return 0;
}