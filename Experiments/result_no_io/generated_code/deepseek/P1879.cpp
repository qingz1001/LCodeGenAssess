#include <stdio.h>
#include <stdbool.h>

#define MOD 100000000
#define MAX_M 12
#define MAX_N 12

int M, N;
int field[MAX_M][MAX_N];
int dp[MAX_M][1 << MAX_N];

bool isValid(int row, int state) {
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
        if (isValid(0, state)) {
            dp[0][state] = 1;
        }
    }

    for (int i = 1; i < M; i++) {
        for (int state = 0; state < (1 << N); state++) {
            if (!isValid(i, state)) continue;
            for (int prevState = 0; prevState < (1 << N); prevState++) {
                if (!isValid(i - 1, prevState)) continue;
                if (state & prevState) continue;
                dp[i][state] = (dp[i][state] + dp[i - 1][prevState]) % MOD;
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