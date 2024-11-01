#include <stdio.h>
#include <stdlib.h>

int main() {
    int A, B;
    scanf("%d %d", &A, &B);
    int N;
    scanf("%d", &N);
    int hotels[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &hotels[i]);
    }

    int dp[7001] = {0};
    dp[0] = 1;

    for (int i = 0; i <= 7000; i++) {
        if (dp[i] == 0) continue;
        for (int j = 0; j < N; j++) {
            if (i + A <= hotels[j]) {
                dp[hotels[j]] += dp[i];
            }
            if (i + B >= hotels[j]) {
                dp[hotels[j]] += dp[i];
            } else {
                break;
            }
        }
    }

    printf("%d\n", dp[7000]);

    return 0;
}