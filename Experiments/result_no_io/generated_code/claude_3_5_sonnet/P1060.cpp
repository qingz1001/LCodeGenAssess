#include <stdio.h>
#include <string.h>

#define MAX_N 30000
#define MAX_M 25

int dp[MAX_N + 1];
int v[MAX_M], p[MAX_M];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &v[i], &p[i]);
    }

    memset(dp, 0, sizeof(dp));

    for (int i = 0; i < m; i++) {
        for (int j = n; j >= v[i]; j--) {
            int value = v[i] * p[i];
            if (dp[j] < dp[j - v[i]] + value) {
                dp[j] = dp[j - v[i]] + value;
            }
        }
    }

    printf("%d\n", dp[n]);

    return 0;
}