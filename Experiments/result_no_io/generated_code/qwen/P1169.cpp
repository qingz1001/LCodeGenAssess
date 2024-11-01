#include <stdio.h>
#include <stdlib.h>

#define MAXN 2005

int N, M;
int board[MAXN][MAXN];
int dp[MAXN][MAXN];

// Function to find the largest square chessboard
int largestSquare() {
    int maxSide = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (board[i][j]) {
                dp[i][j] = 1 + dp[i-1][j-1] & dp[i-1][j] & dp[i][j-1];
                maxSide = fmax(maxSide, dp[i][j]);
            }
        }
    }
    return maxSide * maxSide;
}

// Function to find the largest rectangular chessboard
int largestRectangle() {
    int maxArea = 0;
    for (int i = 1; i <= N; i++) {
        int heights[M+1];
        memset(heights, 0, sizeof(heights));
        for (int j = i; j <= N; j++) {
            for (int k = 1; k <= M; k++) {
                heights[k] += board[j][k];
            }
            int left = -1, right = M + 1;
            for (int k = 1; k <= M; k++) {
                while (left + 1 < k && heights[left + 1] >= heights[k]) {
                    left++;
                }
                while (right - 1 > k && heights[right - 1] >= heights[k]) {
                    right--;
                }
                maxArea = fmax(maxArea, heights[k] * (right - left - 1));
            }
        }
    }
    return maxArea;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            scanf("%d", &board[i][j]);
        }
    }

    printf("%d\n", largestSquare());
    printf("%d\n", largestRectangle());

    return 0;
}