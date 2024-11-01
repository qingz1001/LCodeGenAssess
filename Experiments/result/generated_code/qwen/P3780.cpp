#include <stdio.h>
#include <stdlib.h>

#define MAXN 20005
#define INF 0x3f3f3f3f

typedef struct {
    int parent, apples, value;
} Node;

Node nodes[MAXN];
int dp[MAXN][50001];

int max(int a, int b) {
    return a > b ? a : b;
}

void dfs(int node, int depth, int k) {
    if (nodes[node].apples == 0) {
        for (int i = 0; i <= k; i++) {
            dp[node][i] = -INF;
        }
        return;
    }

    for (int i = 0; i <= k; i++) {
        dp[node][i] = -INF;
    }

    for (int i = 0; i <= nodes[node].apples; i++) {
        dp[node][i] = i * nodes[node].value;
    }

    for (int i = 1; i <= nodes[node].apples; i++) {
        for (int j = 0; j <= k; j++) {
            if (j >= i) {
                dp[node][j] = max(dp[node][j], dp[nodes[node].parent][j - i] + i * nodes[node].value);
            }
        }
    }

    for (int i = 1; i <= k; i++) {
        dp[node][i] = max(dp[node][i], dp[node][i - 1]);
    }
}

int main() {
    int Q;
    scanf("%d", &Q);

    while (Q--) {
        int n, k;
        scanf("%d %d", &n, &k);

        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &nodes[i].parent, &nodes[i].apples, &nodes[i].value);
            nodes[i].parent--;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= k; j++) {
                dp[i][j] = -INF;
            }
        }

        dfs(0, 1, k);

        int result = -INF;
        for (int i = 0; i <= k; i++) {
            result = max(result, dp[0][i] - (depth - 1));
        }

        printf("%d\n", result);
    }

    return 0;
}