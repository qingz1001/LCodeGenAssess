#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 6
#define MAXM 6
#define MAX_STATES (1 << (MAXN * MAXM))

int dp[MAX_STATES];
int matrix[MAXN][MAXM];
int N, M;

int is_valid(int state, int x, int y) {
    int idx = x * M + y;
    if ((state & (1 << idx)) == 0) return 0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < N && ny >= 0 && ny < M) {
                int nidx = nx * M + ny;
                if (state & (1 << nidx)) return 0;
            }
        }
    }
    return 1;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int solve() {
    int total_states = 1 << (N * M);
    memset(dp, 0, sizeof(dp));

    for (int state = 0; state < total_states; state++) {
        for (int x = 0; x < N; x++) {
            for (int y = 0; y < M; y++) {
                if (is_valid(state, x, y)) {
                    int idx = x * M + y;
                    int new_state = state ^ (1 << idx);
                    dp[state] = max(dp[state], dp[new_state] + matrix[x][y]);
                }
            }
        }
    }

    return dp[total_states - 1];
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &N, &M);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                scanf("%d", &matrix[i][j]);
            }
        }
        printf("%d\n", solve());
    }
    return 0;
}