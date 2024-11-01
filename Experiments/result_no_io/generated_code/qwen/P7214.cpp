#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000005
#define INF 1e9

typedef struct {
    int t, l, r, c;
} Treatment;

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    Treatment treatments[m];
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d %d", &treatments[i].t, &treatments[i].l, &treatments[i].r, &treatments[i].c);
    }
    
    int *dp = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; ++i) {
        dp[i] = INF;
    }
    dp[0] = 0;
    
    for (int i = 0; i < m; ++i) {
        int t = treatments[i].t, l = treatments[i].l - 1, r = treatments[i].r - 1, c = treatments[i].c;
        for (int j = n; j >= l; --j) {
            dp[j] = dp[fmin(j - 1, r)] + c;
        }
    }
    
    int ans = dp[n];
    if (ans == INF) {
        printf("-1\n");
    } else {
        printf("%d\n", ans);
    }
    
    free(dp);
    return 0;
}