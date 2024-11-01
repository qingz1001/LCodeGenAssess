#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 150

typedef struct Node {
    int id;
    struct Node* children[MAXN];
    int child_count;
} Node;

Node nodes[MAXN];
int dp[MAXN][MAXN];
int N, P;

void init_nodes() {
    for (int i = 1; i <= N; i++) {
        nodes[i].id = i;
        nodes[i].child_count = 0;
    }
}

void add_edge(int parent, int child) {
    nodes[parent].children[nodes[parent].child_count++] = &nodes[child];
}

int min(int a, int b) {
    return a < b ? a : b;
}

void dfs(int u) {
    dp[u][1] = nodes[u].child_count;
    for (int i = 0; i < nodes[u].child_count; i++) {
        int v = nodes[u].children[i]->id;
        dfs(v);
        for (int j = P; j >= 1; j--) {
            for (int k = 1; k < j; k++) {
                dp[u][j] = min(dp[u][j], dp[u][j - k] + dp[v][k] - 1);
            }
        }
    }
}

int main() {
    scanf("%d %d", &N, &P);
    init_nodes();

    for (int i = 1; i < N; i++) {
        int I, J;
        scanf("%d %d", &I, &J);
        add_edge(I, J);
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            dp[i][j] = INT_MAX;
        }
    }

    dfs(1);

    int result = dp[1][P];
    for (int i = 2; i <= N; i++) {
        result = min(result, dp[i][P] + 1);
    }

    printf("%d\n", result);

    return 0;
}