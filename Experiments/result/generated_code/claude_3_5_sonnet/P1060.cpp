#include <stdio.h>
#include <string.h>

#define MAX_N 30000
#define MAX_M 25

int dp[MAX_N + 1];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    memset(dp, 0, sizeof(dp));

    for (int i = 0; i < m; i++) {
        int v, p;
        scanf("%d %d", &v, &p);
        
        for (int j = n; j >= v; j--) {
            if (dp[j] < dp[j - v] + v * p) {
                dp[j] = dp[j - v] + v * p;
            }
        }
    }

    printf("%d\n", dp[n]);

    return 0;
}