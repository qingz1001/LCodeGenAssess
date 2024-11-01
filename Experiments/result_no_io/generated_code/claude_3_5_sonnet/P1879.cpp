#include <stdio.h>
#include <string.h>

#define MOD 100000000
#define MAXN 12
#define MAXS 4096

int M, N;
int field[MAXN];
int dp[MAXN][MAXS];

int main() {
    scanf("%d %d", &M, &N);
    
    for (int i = 0; i < M; i++) {
        int row = 0;
        for (int j = 0; j < N; j++) {
            int x;
            scanf("%d", &x);
            row = (row << 1) | x;
        }
        field[i] = row;
    }

    int maxState = 1 << N;
    
    for (int state = 0; state < maxState; state++) {
        if ((state & (state << 1)) == 0 && (state & field[0]) == state) {
            dp[0][state] = 1;
        }
    }

    for (int i = 1; i < M; i++) {
        for (int state = 0; state < maxState; state++) {
            if ((state & (state << 1)) == 0 && (state & field[i]) == state) {
                for (int prevState = 0; prevState < maxState; prevState++) {
                    if ((prevState & state) == 0) {
                        dp[i][state] = (dp[i][state] + dp[i-1][prevState]) % MOD;
                    }
                }
            }
        }
    }

    int result = 0;
    for (int state = 0; state < maxState; state++) {
        result = (result + dp[M-1][state]) % MOD;
    }

    printf("%d\n", result);

    return 0;
}