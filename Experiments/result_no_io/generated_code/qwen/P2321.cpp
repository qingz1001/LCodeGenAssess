#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int *a = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    int dp[MAXN];
    for (int i = 1; i <= n; i++) {
        dp[i] = 1;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (a[j] < a[i]) {
                dp[i] = dp[i] > dp[j] + 1 ? dp[i] : dp[j] + 1;
            }
        }
    }

    int max_length = 0;
    for (int i = 1; i <= n; i++) {
        if (dp[i] > max_length) {
            max_length = dp[i];
        }
    }

    printf("%d\n", max_length);

    free(a);
    return 0;
}