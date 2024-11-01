#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 2000

int matrix[MAXN][MAXN];
int dp[MAXN][MAXN];
int left[MAXN], right[MAXN], height[MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    // 计算最大正方形面积
    int max_square = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 1;
            } else if (matrix[i][j] != matrix[i-1][j] && matrix[i][j] != matrix[i][j-1] && matrix[i][j] == matrix[i-1][j-1]) {
                dp[i][j] = min(dp[i-1][j], min(dp[i][j-1], dp[i-1][j-1])) + 1;
            } else {
                dp[i][j] = 1;
            }
            max_square = max(max_square, dp[i][j] * dp[i][j]);
        }
    }

    // 计算最大矩形面积
    int max_rectangle = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (i == 0) {
                height[j] = 1;
            } else if (matrix[i][j] != matrix[i-1][j]) {
                height[j]++;
            } else {
                height[j] = 1;
            }
        }
        for (int j = 0; j < M; j++) {
            left[j] = j;
            while (left[j] > 0 && height[left[j] - 1] >= height[j]) {
                left[j] = left[left[j] - 1];
            }
        }
        for (int j = M - 1; j >= 0; j--) {
            right[j] = j;
            while (right[j] < M - 1 && height[right[j] + 1] >= height[j]) {
                right[j] = right[right[j] + 1];
            }
        }
        for (int j = 0; j < M; j++) {
            max_rectangle = max(max_rectangle, height[j] * (right[j] - left[j] + 1));
        }
    }

    printf("%d\n%d\n", max_square, max_rectangle);

    return 0;
}