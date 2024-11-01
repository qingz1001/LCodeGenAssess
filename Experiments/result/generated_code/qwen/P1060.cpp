#include <stdio.h>

#define MAX_N 30000
#define MAX_M 25
#define MAX_V 10000
#define MAX_P 5

int n, m;
int v[MAX_M], p[MAX_M];
int dp[MAX_N + 1];

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &v[i], &p[i]);
    }

    for (int i = 0; i < m; i++) {
        for (int j = n; j >= v[i]; j--) {
            dp[j] = max(dp[j], dp[j - v[i]] + v[i] * p[i]);
        }
    }

    printf("%d\n", dp[n]);
    return 0;
}