#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1005
#define MAX_M 1005

int a[MAX_N], b[MAX_N];
int c1[MAX_M], c2[MAX_M];
int combination[MAX_M][MAX_N];

int max(int x, int y) {
    return (x > y) ? x : y;
}

int main() {
    int n, m, k;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &b[i]);
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d", &k, &c1[i], &c2[i]);
        for (int j = 1; j <= k; j++) {
            scanf("%d", &combination[i][j]);
        }
    }

    int dp_a[1 << n] = {0};
    int dp_b[1 << n] = {0};

    for (int mask = 1; mask < (1 << n); mask++) {
        int count = __builtin_popcount(mask);
        for (int i = 1; i <= m; i++) {
            int valid = 1;
            for (int j = 1; j <= combination[i][0]; j++) {
                if (!(mask & (1 << combination[i][j]))) {
                    valid = 0;
                    break;
                }
            }
            if (valid) {
                dp_a[mask] += c1[i];
                dp_b[mask] += c2[i];
            }
        }
        for (int i = 1; i <= n; i++) {
            if (mask & (1 << i)) {
                dp_a[mask] += a[i];
                dp_b[mask] += b[i];
            }
        }
    }

    int result = 0;
    for (int mask = 1; mask < (1 << n); mask++) {
        result = max(result, dp_a[mask] + dp_b[mask ^ ((1 << n) - 1)]);
    }

    printf("%d\n", result);

    return 0;
}