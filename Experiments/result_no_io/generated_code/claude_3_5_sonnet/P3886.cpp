#include <stdio.h>
#include <string.h>

#define MAX_N 9
#define MAX_STATE (1 << MAX_N * MAX_N)

int N;
int grid[MAX_N][MAX_N];
int dp[MAX_STATE];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    memset(dp, -0x3f, sizeof(dp));
    dp[0] = 0;

    int full_state = (1 << (N * N)) - 1;
    for (int state = 0; state <= full_state; state++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int pos = i * N + j;
                if (!(state & (1 << pos))) continue;

                int curr_sum = dp[state];
                if (i > 0 && !(state & (1 << ((i-1)*N + j)))) {
                    dp[state | (1 << ((i-1)*N + j))] = max(dp[state | (1 << ((i-1)*N + j))], curr_sum + grid[i-1][j]);
                }
                if (i < N-1 && !(state & (1 << ((i+1)*N + j)))) {
                    dp[state | (1 << ((i+1)*N + j))] = max(dp[state | (1 << ((i+1)*N + j))], curr_sum + grid[i+1][j]);
                }
                if (j > 0 && !(state & (1 << (i*N + j-1)))) {
                    dp[state | (1 << (i*N + j-1))] = max(dp[state | (1 << (i*N + j-1))], curr_sum + grid[i][j-1]);
                }
                if (j < N-1 && !(state & (1 << (i*N + j+1)))) {
                    dp[state | (1 << (i*N + j+1))] = max(dp[state | (1 << (i*N + j+1))], curr_sum + grid[i][j+1]);
                }
            }
        }
    }

    int result = -0x3f3f3f3f;
    for (int state = 0; state <= full_state; state++) {
        result = max(result, dp[state]);
    }

    printf("%d\n", result);
    return 0;
}