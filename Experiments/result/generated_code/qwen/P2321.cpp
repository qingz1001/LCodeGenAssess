#include <stdio.h>
#include <stdlib.h>

#define MAXN 10005

int main() {
    int n, m;
    scanf("%d", &n);
    int *a = (int *)malloc((n + 1) * sizeof(int));
    int *b = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &a[i], &b[i]);
    }

    int dp[MAXN];
    for (int i = 1; i <= n; i++) {
        dp[i] = 1;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j && a[i] > a[j] && b[i] > b[j]) {
                dp[i] = dp[j] + 1;
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
    free(b);

    return 0;
}