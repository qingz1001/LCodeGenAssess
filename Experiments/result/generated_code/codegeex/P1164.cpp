#include <stdio.h>

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int a[100] = {0};
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    int dp[10001] = {0};
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = m; j >= a[i]; j--) {
            dp[j] += dp[j - a[i]];
        }
    }
    printf("%d\n", dp[m]);
    return 0;
}