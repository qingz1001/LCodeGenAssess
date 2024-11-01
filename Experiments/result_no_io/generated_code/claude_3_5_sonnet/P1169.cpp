#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 2000
#define MAX_M 2000

int n, m;
int board[MAX_N][MAX_M];
int up[MAX_N][MAX_M], left[MAX_N][MAX_M], right[MAX_N][MAX_M];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int largest_square() {
    int i, j, max_size = 0;
    int dp[MAX_N][MAX_M];
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 1;
            } else if (board[i][j] != board[i-1][j] && board[i][j] != board[i][j-1] && board[i][j] != board[i-1][j-1]) {
                dp[i][j] = min(dp[i-1][j], min(dp[i][j-1], dp[i-1][j-1])) + 1;
            } else {
                dp[i][j] = 1;
            }
            max_size = max(max_size, dp[i][j]);
        }
    }
    
    return max_size * max_size;
}

int largest_rectangle() {
    int i, j, max_area = 0;
    
    for (j = 0; j < m; j++) {
        up[0][j] = 1;
        for (i = 1; i < n; i++) {
            if (board[i][j] != board[i-1][j]) {
                up[i][j] = up[i-1][j] + 1;
            } else {
                up[i][j] = 1;
            }
        }
    }
    
    for (i = 0; i < n; i++) {
        left[i][0] = 1;
        for (j = 1; j < m; j++) {
            if (board[i][j] != board[i][j-1]) {
                left[i][j] = left[i][j-1] + 1;
            } else {
                left[i][j] = 1;
            }
        }
        
        right[i][m-1] = 1;
        for (j = m-2; j >= 0; j--) {
            if (board[i][j] != board[i][j+1]) {
                right[i][j] = right[i][j+1] + 1;
            } else {
                right[i][j] = 1;
            }
        }
    }
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            int height = up[i][j];
            int width = left[i][j] + right[i][j] - 1;
            max_area = max(max_area, height * width);
        }
    }
    
    return max_area;
}

int main() {
    int i, j;
    
    scanf("%d %d", &n, &m);
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &board[i][j]);
        }
    }
    
    printf("%d\n", largest_square());
    printf("%d\n", largest_rectangle());
    
    return 0;
}