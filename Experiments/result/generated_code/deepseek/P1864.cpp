#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 70

typedef struct {
    int data, weight, freq;
} Node;

Node nodes[MAXN];
int N, K;
int dp[MAXN][MAXN][MAXN];

int cmp(const void *a, const void *b) {
    return ((Node *)a)->weight - ((Node *)b)->weight;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int dfs(int l, int r, int w) {
    if (l > r) return 0;
    if (dp[l][r][w] != -1) return dp[l][r][w];

    int cost = INT_MAX;
    for (int i = l; i <= r; i++) {
        int left_cost = dfs(l, i - 1, w);
        int right_cost = dfs(i + 1, r, w);
        int root_cost = nodes[i].freq * (w + 1);
        cost = min(cost, left_cost + right_cost + root_cost);
    }

    if (w < N) {
        for (int i = l; i <= r; i++) {
            int left_cost = dfs(l, i - 1, w + 1);
            int right_cost = dfs(i + 1, r, w + 1);
            int root_cost = nodes[i].freq * (w + 1);
            cost = min(cost, left_cost + right_cost + root_cost + K);
        }
    }

    dp[l][r][w] = cost;
    return cost;
}

int main() {
    scanf("%d %d", &N, &K);
    for (int i = 0; i < N; i++) scanf("%d", &nodes[i].data);
    for (int i = 0; i < N; i++) scanf("%d", &nodes[i].weight);
    for (int i = 0; i < N; i++) scanf("%d", &nodes[i].freq);

    qsort(nodes, N, sizeof(Node), cmp);

    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < MAXN; j++)
            for (int k = 0; k < MAXN; k++)
                dp[i][j][k] = -1;

    int result = dfs(0, N - 1, 0);
    printf("%d\n", result);

    return 0;
}