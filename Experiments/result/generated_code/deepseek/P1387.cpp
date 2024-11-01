#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int min(int a, int b, int c) {
    int min = a;
    if (b < min) min = b;
    if (c < min) min = c;
    return min;
}

int main() {
    int n, m;
    int matrix[MAX][MAX];
    int dp[MAX][MAX];
    int max_side = 0;

    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &matrix[i][j]);
            if (matrix[i][j] == 1) {
                if (i == 0 || j == 0) {
                    dp[i][j] = 1;
                } else {
                    dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1;
                }
                if (dp[i][j] > max_side) {
                    max_side = dp[i][j];
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }

    printf("%d\n", max_side);

    return 0;
}