#include <stdio.h>

#define MAX_N 100
#define MAX_M 10000

int main() {
    int N, M;
    int a[MAX_N];
    int dp[MAX_M + 1] = {0};

    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
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