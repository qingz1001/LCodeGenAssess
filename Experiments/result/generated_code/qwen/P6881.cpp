#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005

int main() {
    int N, Q;
    scanf("%d %d", &N, &Q);
    long long S[MAXN];
    for (int i = 0; i < N; ++i) {
        scanf("%lld", &S[i]);
    }

    long long dp[MAXN][2];
    for (int i = 0; i < N; ++i) {
        dp[i][0] = 0;
        dp[i][1] = S[i];
    }
    for (int i = 1; i < N; ++i) {
        dp[i][0] = dp[i - 1][1];
        dp[i][1] = fmax(dp[i - 1][1], dp[i][1]);
    }

    long long result[MAXN];
    for (int j = 0; j < Q; ++j) {
        int T, L, R;
        scanf("%d %d %d", &T, &L, &R);
        --L;
        --R;

        if (L == R) {
            result[j] = S[L];
        } else {
            if (T == 1) {
                result[j] = dp[R][1] - dp[L][0];
            } else {
                result[j] = dp[R][1] - dp[L][1];
            }
        }
    }

    for (int j = 0; j < Q; ++j) {
        printf("%lld\n", result[j]);
    }

    return 0;
}