#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 50001
#define MAXM 50001

typedef struct {
    int s_l, s_r, t_l, t_r, w;
} TunnelGroup;

int n, m;
int v[MAXN];
TunnelGroup tunnels[MAXM];

int min(int a, int b) {
    return a < b ? a : b;
}

int abs(int x) {
    return x < 0 ? -x : x;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d %d %d", &tunnels[i].s_l, &tunnels[i].s_r, &tunnels[i].t_l, &tunnels[i].t_r, &tunnels[i].w);
    }

    // Initialize DP array
    int dp[MAXN];
    for (int i = 1; i <= n; i++) {
        dp[i] = INT_MAX;
    }
    dp[1] = 0;

    // Process each tunnel group
    for (int i = 0; i < m; i++) {
        for (int s = tunnels[i].s_l; s <= tunnels[i].s_r; s++) {
            for (int t = tunnels[i].t_l; t <= tunnels[i].t_r; t++) {
                if (dp[s] != INT_MAX) {
                    dp[t] = min(dp[t], dp[s] + tunnels[i].w);
                }
            }
        }
    }

    // Process digging tunnels
    for (int i = 1; i <= n; i++) {
        if (v[i] != 0) {
            for (int j = 1; j <= n; j++) {
                if (dp[i] != INT_MAX) {
                    dp[j] = min(dp[j], dp[i] + abs(i - j) * v[i]);
                }
            }
        }
    }

    // Output result
    if (dp[n] == INT_MAX) {
        printf("-1\n");
    } else {
        printf("%d\n", dp[n]);
        printf("0\n"); // No solution provided for the path
    }

    return 0;
}