#include <stdio.h>
#include <stdlib.h>

#define MAX_R 500
#define MAX_C 500
#define MAX_N 4000

int R, C, A, B;
int N[MAX_R][MAX_C];
int dp[MAX_R + 1][MAX_C + 1];

void read_input() {
    scanf("%d %d %d %d", &R, &C, &A, &B);
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            scanf("%d", &N[i][j]);
        }
    }
}

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int solve() {
    for (int i = 0; i <= R; i++) {
        for (int j = 0; j <= C; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i <= A; i++) {
        for (int j = 1; j <= B; j++) {
            int sum = 0;
            for (int k = 0; k < i - 1; k++) {
                int max_val = 0;
                for (int l = 0; l < j - 1; l++) {
                    max_val = max(max_val, N[k][l]);
                }
                sum += max_val;
            }
            dp[i][j] = sum;
        }
    }

    int result = 0;
    for (int i = 1; i <= A; i++) {
        for (int j = 1; j <= B; j++) {
            result = max(result, dp[i][j]);
        }
    }

    return result;
}

int main() {
    read_input();
    printf("%d\n", solve());
    return 0;
}