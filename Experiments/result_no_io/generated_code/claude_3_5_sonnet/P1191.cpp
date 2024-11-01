#include <stdio.h>
#include <string.h>

#define MAXN 155

char grid[MAXN][MAXN];
int sum[MAXN][MAXN];
int n;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", grid[i] + 1);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + (grid[i][j] == 'W');
        }
    }

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            int start = 1;
            for (int k = 1; k <= n; k++) {
                int count = sum[j][k] - sum[i-1][k] - sum[j][start-1] + sum[i-1][start-1];
                if (count != k - start + 1) {
                    start = k + 1;
                } else {
                    ans += k - start + 1;
                }
            }
        }
    }

    printf("%lld\n", ans);
    return 0;
}