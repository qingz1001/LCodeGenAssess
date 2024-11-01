#include <stdio.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    int a[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    int dp[M + 1];
    for (int i = 0; i <= M; i++) {
        dp[i] = 0;
    }
    dp[0] = 1;

    for (int i = 0; i < N; i++) {
        for (int j = M; j >= a[i]; j--) {
            dp[j] += dp[j - a[i]];
        }
    }

    printf("%d\n", dp[M]);
    return 0;
}