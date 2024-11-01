#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    int a[1005];
    int sum = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        sum += a[i];
    }
    if (sum < 0) {
        printf("Impossible\n");
        return 0;
    }
    int dp[1000005];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = sum; j >= 0; j--) {
            if (dp[j]) {
                dp[j + a[i]] = 1;
            }
        }
    }
    for (int i = sum; i >= 0; i--) {
        if (dp[i]) {
            printf("%d\n", i);
            break;
        }
    }
    return 0;
}