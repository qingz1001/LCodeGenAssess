#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000

int n;
int v[MAXN];

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }

    int dp[2][2];
    dp[0][0] = 0;
    dp[0][1] = 0;
    dp[1][0] = 0;
    dp[1][1] = 0;

    for (int i = 0; i < n; i++) {
        int new_dp[2][2];
        new_dp[0][0] = dp[0][1];
        new_dp[0][1] = max(dp[0][0], dp[1][0] + v[i]);
        new_dp[1][0] = dp[1][1];
        new_dp[1][1] = max(dp[1][0], dp[0][1] + v[(i + 1) % n]);
        for (int j = 0; j < 2; j++) {
            dp[j][0] = new_dp[j][0];
            dp[j][1] = new_dp[j][1];
        }
    }

    printf("%d\n", max(dp[0][0], dp[1][0]));
    return 0;
}