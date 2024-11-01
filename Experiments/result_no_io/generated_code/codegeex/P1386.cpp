#include <stdio.h>
#include <string.h>

#define MAXN 301

int n, m, M;
int fixed[MAXN];
long long dp[MAXN];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &M);
        memset(fixed, 0, sizeof(fixed));
        for (int i = 0; i < m; i++) {
            int p, q;
            scanf("%d%d", &p, &q);
            fixed[q]++;
        }

        bool valid = true;
        for (int i = 1; i <= n; i++) {
            if (fixed[i] > 1) {
                valid = false;
                break;
            }
        }

        if (!valid) {
            printf("NO\n");
            continue;
        }

        dp[0] = 1;
        for (int i = 1; i <= n; i++) {
            if (fixed[i]) {
                dp[i] = dp[i - 1];
            } else {
                dp[i] = (dp[i - 1] + dp[i - 2]) % M;
            }
        }

        printf("YES %lld\n", dp[n]);
    }
    return 0;
}