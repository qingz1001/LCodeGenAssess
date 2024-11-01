#include <stdio.h>
#include <stdlib.h>

#define MAX_N 2005

int dp[MAX_N][MAX_N];

int max_square(int N, int M, int board[MAX_N][MAX_N]) {
    int max_side = 0;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            if (board[i-1][j-1] == 0 && board[i-1][j] == 1 && board[i][j-1] == 1 && board[i][j] == 0) {
                dp[i][j] = 1;
                max_side = 1;
            } else if (dp[i-1][j-1] > 0) {
                if (board[i-1][j] == board[i][j-1] && board[i][j] != board[i-1][j-1]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                    max_side = dp[i][j];
                }
            }
        }
    }
    return max_side * max_side;
}

int max_rectangle(int N, int M, int board[MAX_N][MAX_N]) {
    int max_area = 0;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            dp[i][j] = board[i-1][j-1];
        }
        for (int j = 1; j <= M; ++j) {
            for (int k = j; k <= M; ++k) {
                int min_height = INT_MAX;
                for (int l = i; l <= N; ++l) {
                    min_height = (min_height < dp[l][k]) ? min_height : dp[l][k];
                    dp[l][k] -= dp[l][j-1];
                    max_area = (max_area < min_height * (k - j + 1)) ? max_area : min_height * (k - j + 1);
                }
            }
        }
    }
    return max_area;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    int board[MAX_N][MAX_N];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            scanf("%d", &board[i][j]);
        }
    }
    printf("%d\n%d\n", max_square(N, M, board), max_rectangle(N, M, board));
    return 0;
}