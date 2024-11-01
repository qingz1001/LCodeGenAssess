#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

#define MAXN 51
#define MAXM 1001
#define MAXQ 100001

typedef struct {
    int from, to, weight;
} Edge;

Edge edges[MAXM];
double dp[MAXN][MAXN][MAXN];

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &edges[i].from, &edges[i].to, &edges[i].weight);
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            for (int k = 1; k <= N; k++) {
                dp[i][j][k] = DBL_MAX;
            }
        }
    }

    for (int i = 0; i < M; i++) {
        int u = edges[i].from;
        int v = edges[i].to;
        int w = edges[i].weight;
        dp[u][v][1] = w;
    }

    for (int len = 2; len <= N; len++) {
        for (int k = 1; k <= N; k++) {
            for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= N; j++) {
                    if (dp[i][k][len-1] < DBL_MAX && dp[k][j][1] < DBL_MAX) {
                        dp[i][j][len] = fmin(dp[i][j][len], dp[i][k][len-1] + dp[k][j][1]);
                    }
                }
            }
        }
    }

    int Q;
    scanf("%d", &Q);

    for (int q = 0; q < Q; q++) {
        int X, Y;
        scanf("%d %d", &X, &Y);

        double min_density = DBL_MAX;
        for (int len = 1; len <= N; len++) {
            if (dp[X][Y][len] < DBL_MAX) {
                double density = dp[X][Y][len] / len;
                if (density < min_density) {
                    min_density = density;
                }
            }
        }

        if (min_density < DBL_MAX) {
            printf("%.3f\n", min_density);
        } else {
            printf("OMG!\n");
        }
    }

    return 0;
}