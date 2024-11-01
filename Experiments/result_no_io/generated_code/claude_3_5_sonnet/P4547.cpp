#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAXN 15
#define MAXM 225

int n, m;
int dp[1 << MAXN];
int graph[MAXN][MAXN];
int type[MAXM], a1[MAXM], b1[MAXM], a2[MAXM], b2[MAXM];

int mul(int a, int b) {
    return (long long)a * b % MOD;
}

int add(int a, int b) {
    return (a + b) % MOD;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &type[i]);
        if (type[i] == 0) {
            scanf("%d%d", &a1[i], &b1[i]);
            a1[i]--; b1[i]--;
        } else {
            scanf("%d%d%d%d", &a1[i], &b1[i], &a2[i], &b2[i]);
            a1[i]--; b1[i]--; a2[i]--; b2[i]--;
        }
    }

    dp[0] = 1;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (dp[mask] == 0) continue;
        int i = __builtin_popcount(mask);
        if (i == n) continue;

        memset(graph, 0, sizeof(graph));
        for (int j = 0; j < m; j++) {
            if (type[j] == 0) {
                if ((mask & (1 << a1[j])) == 0) {
                    graph[a1[j]][b1[j]] = add(graph[a1[j]][b1[j]], 1);
                }
            } else if (type[j] == 1) {
                if ((mask & (1 << a1[j])) == 0 && (mask & (1 << a2[j])) == 0) {
                    graph[a1[j]][b1[j]] = add(graph[a1[j]][b1[j]], 1);
                    graph[a2[j]][b2[j]] = add(graph[a2[j]][b2[j]], 1);
                }
            } else {
                if ((mask & (1 << a1[j])) == 0 && (mask & (1 << a2[j])) == 0) {
                    graph[a1[j]][b1[j]] = add(graph[a1[j]][b1[j]], 1);
                    graph[a2[j]][b2[j]] = add(graph[a2[j]][b2[j]], 1);
                }
            }
        }

        for (int j = 0; j < n; j++) {
            if ((mask & (1 << j)) == 0) {
                for (int k = 0; k < n; k++) {
                    dp[mask | (1 << j)] = add(dp[mask | (1 << j)], mul(dp[mask], graph[j][k]));
                }
            }
        }
    }

    printf("%d\n", dp[(1 << n) - 1]);
    return 0;
}