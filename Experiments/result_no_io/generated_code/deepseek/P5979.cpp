#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000007
#define MAXN 1000005

int n;
int c[MAXN], d[MAXN];
int dp[MAXN], ways[MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &c[i], &d[i]);
    }

    dp[0] = 0;
    ways[0] = 1;

    for (int i = 1; i <= n; i++) {
        int max_group_size = d[i];
        int min_group_size = c[i];
        int max_start = i - min_group_size + 1;
        int min_start = i - max_group_size + 1;

        if (min_start < 1) {
            min_start = 1;
        }

        if (max_start < 1) {
            dp[i] = -1;
            continue;
        }

        dp[i] = -1;
        for (int j = min_start; j <= max_start; j++) {
            if (dp[j - 1] != -1) {
                int new_groups = dp[j - 1] + 1;
                if (new_groups > dp[i]) {
                    dp[i] = new_groups;
                    ways[i] = ways[j - 1];
                } else if (new_groups == dp[i]) {
                    ways[i] = (ways[i] + ways[j - 1]) % MOD;
                }
            }
        }
    }

    if (dp[n] == -1) {
        printf("NIE\n");
    } else {
        printf("%d %d\n", dp[n], ways[n]);
    }

    return 0;
}