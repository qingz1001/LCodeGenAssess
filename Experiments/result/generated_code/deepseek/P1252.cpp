#include <stdio.h>
#include <limits.h>

#define N 5
#define K 10
#define TOTAL_DISTANCE 25

int times[N][K];
int dp[N + 1][TOTAL_DISTANCE + 1];
int path[N + 1][TOTAL_DISTANCE + 1];

void read_input() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            scanf("%d", &times[i][j]);
        }
    }
}

void solve() {
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= TOTAL_DISTANCE; j++) {
            dp[i][j] = INT_MAX;
        }
    }
    dp[0][0] = 0;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= TOTAL_DISTANCE; j++) {
            for (int k = 1; k <= K && k <= j; k++) {
                if (dp[i - 1][j - k] != INT_MAX && dp[i - 1][j - k] + times[i - 1][k - 1] < dp[i][j]) {
                    dp[i][j] = dp[i - 1][j - k] + times[i - 1][k - 1];
                    path[i][j] = k;
                }
            }
        }
    }
}

void print_result() {
    printf("%d\n", dp[N][TOTAL_DISTANCE]);
    int distances[N];
    int i = N, j = TOTAL_DISTANCE;
    while (i > 0) {
        distances[i - 1] = path[i][j];
        j -= path[i][j];
        i--;
    }
    for (int i = 0; i < N; i++) {
        printf("%d ", distances[i]);
    }
    printf("\n");
}

int main() {
    read_input();
    solve();
    print_result();
    return 0;
}