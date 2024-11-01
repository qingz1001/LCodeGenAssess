#include <stdio.h>
#include <stdlib.h>

#define MAX_N 50
#define MAX_H 400
#define MAX_T 400

typedef struct {
    int volume;
    int mass;
    int calories;
} Food;

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int h, t, n;
    Food foods[MAX_N];
    int dp[MAX_H + 1][MAX_T + 1];

    // Initialize dp array
    for (int i = 0; i <= MAX_H; i++) {
        for (int j = 0; j <= MAX_T; j++) {
            dp[i][j] = 0;
        }
    }

    // Read input
    scanf("%d %d", &h, &t);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &foods[i].volume, &foods[i].mass, &foods[i].calories);
    }

    // Dynamic programming to find the maximum calories
    for (int i = 0; i < n; i++) {
        for (int j = h; j >= foods[i].volume; j--) {
            for (int k = t; k >= foods[i].mass; k--) {
                dp[j][k] = max(dp[j][k], dp[j - foods[i].volume][k - foods[i].mass] + foods[i].calories);
            }
        }
    }

    // Output the result
    printf("%d\n", dp[h][t]);

    return 0;
}