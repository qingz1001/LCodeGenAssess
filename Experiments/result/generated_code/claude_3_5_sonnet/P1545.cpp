#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_L 1000001
#define MAX_N 1001

int N, L, A, B;
int dp[MAX_L];
int event[MAX_L * 2];

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d %d", &N, &L);
    scanf("%d %d", &A, &B);

    memset(event, 0, sizeof(event));
    for (int i = 0; i < N; i++) {
        int S, E;
        scanf("%d %d", &S, &E);
        event[S]++;
        event[E + 1]--;
    }

    int count = 0;
    for (int i = 1; i <= L; i++) {
        count += event[i];
        if (count > 0) {
            event[i] = 1;
        } else {
            event[i] = 0;
        }
    }

    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;

    for (int i = 1; i <= L; i++) {
        if (!event[i]) {
            dp[i] = dp[i-1];
            continue;
        }

        for (int j = A; j <= B && i - j >= 0; j++) {
            dp[i] = min(dp[i], dp[max(0, i - 2*j - 1)] + 1);
        }

        if (dp[i] > 1000000) {
            printf("-1\n");
            return 0;
        }
    }

    printf("%d\n", dp[L]);
    return 0;
}