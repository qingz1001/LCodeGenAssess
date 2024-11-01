#include <stdio.h>
#include <stdbool.h>

#define MOD 100000000
#define MAX_M 12
#define MAX_N 12

int M, N;
int field[MAX_M][MAX_N];
int dp[MAX_M][1 << MAX_N];

bool is_valid(int row, int state) {
    for (int i = 0; i < N - 1; i++) {
        if ((state & (1 << i)) && (state & (1 << (i + 1)))) {
            return false;
        }
    }
    for (int i = 0; i < N; i++) {
        if ((state & (1 << i)) && field[row][i] == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    scanf("%d %d", &M, &N);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &field[i][j]);
        }
    }

    for (int state = 0; state < (1 << N); state++) {
        if (is_valid(0, state)) {
            dp[0][state] = 1;
        }
    }

    for (int i = 1; i < M; i++) {
        for (int state = 0; state < (1 << N); state++) {
            if (!is_valid(i, state)) continue;
            for (int prev_state = 0; prev_state < (1 << N); prev_state++) {
                if (!is_valid(i - 1, prev_state)) continue;
                bool conflict = false;
                for (int j = 0; j < N; j++) {
                    if ((state & (1 << j)) && (prev_state & (1 << j))) {
                        conflict = true;
                        break;
                    }
                }
                if (!conflict) {
                    dp[i][state] = (dp[i][state] + dp[i - 1][prev_state]) % MOD;
                }
            }
        }
    }

    int result = 0;
    for (int state = 0; state < (1 << N); state++) {
        result = (result + dp[M - 1][state]) % MOD;
    }

    printf("%d\n", result);
    return 0;
}