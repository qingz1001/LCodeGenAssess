#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005
#define MAXM 5005

int n, m;
int F[MAXN];
int T[MAXM][2];
double dp[MAXN][MAXN];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &F[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &T[i][0], &T[i][1], &T[i][2]);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = -1;
        }
    }

    double max_avg = 0;

    for (int k = 0; k < m; k++) {
        int u = T[k][0], v = T[k][1], t = T[k][2];
        if (dp[u][v] == -1) {
            dp[u][v] = F[v] / (double)t;
            max_avg = fmax(max_avg, dp[u][v]);
        } else {
            dp[u][v] = fmax(dp[u][v], F[v] / (double)t + dp[v][u]);
            max_avg = fmax(max_avg, dp[u][v]);
        }
    }

    printf("%.2f\n", max_avg);

    return 0;
}