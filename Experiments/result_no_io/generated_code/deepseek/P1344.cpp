#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 32
#define MAXM 1000

typedef struct {
    int from, to, cost;
} Edge;

int N, M;
Edge edges[MAXM];
int dp[1 << MAXN];
int count[1 << MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &edges[i].from, &edges[i].to, &edges[i].cost);
        edges[i].from--;
        edges[i].to--;
    }

    for (int i = 0; i < (1 << N); i++) {
        dp[i] = INT_MAX;
        count[i] = INT_MAX;
    }

    dp[1] = 0;
    count[1] = 0;

    for (int mask = 0; mask < (1 << N); mask++) {
        if (dp[mask] == INT_MAX) continue;
        for (int i = 0; i < M; i++) {
            if ((mask & (1 << edges[i].from)) && !(mask & (1 << edges[i].to))) {
                int new_mask = mask | (1 << edges[i].to);
                if (dp[new_mask] > dp[mask] + edges[i].cost) {
                    dp[new_mask] = dp[mask] + edges[i].cost;
                    count[new_mask] = count[mask] + 1;
                } else if (dp[new_mask] == dp[mask] + edges[i].cost) {
                    count[new_mask] = min(count[new_mask], count[mask] + 1);
                }
            }
        }
    }

    printf("%d %d\n", dp[(1 << N) - 1], count[(1 << N) - 1]);

    return 0;
}