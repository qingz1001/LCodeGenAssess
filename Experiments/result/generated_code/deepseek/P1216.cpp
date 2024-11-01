#include <stdio.h>
#include <stdlib.h>

#define MAX_R 1000

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int r;
    scanf("%d", &r);

    int triangle[MAX_R][MAX_R];
    int dp[MAX_R][MAX_R];

    for (int i = 0; i < r; i++) {
        for (int j = 0; j <= i; j++) {
            scanf("%d", &triangle[i][j]);
        }
    }

    // Initialize the dp array with the values from the last row of the triangle
    for (int j = 0; j < r; j++) {
        dp[r-1][j] = triangle[r-1][j];
    }

    // Fill the dp array from bottom to top
    for (int i = r - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            dp[i][j] = triangle[i][j] + max(dp[i+1][j], dp[i+1][j+1]);
        }
    }

    // The maximum sum is now at dp[0][0]
    printf("%d\n", dp[0][0]);

    return 0;
}