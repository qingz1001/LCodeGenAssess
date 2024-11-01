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
        for (int j = i - 1; j >= 0; j--) {
            max_group_size = min(max_group_size, d[j + 1]);
            min_group_size = max(min_group_size, c[j + 1]);
            if (max_group_size < min_group_size) break;
            if (i - j >= min_group_size && i - j <= max_group_size) {
                if (dp[i] < dp[j] + 1) {
                    dp[i] = dp[j] + 1;
                    ways[i] = ways[j];
                } else if (dp[i] == dp[j] + 1) {
                    ways[i] = (ways[i] + ways[j]) % MOD;
                }
            }
        }
    }

    if (dp[n] == 0) {
        printf("NIE\n");
    } else {
        printf("%d %d\n", dp[n], ways[n]);
    }

    return 0;
}