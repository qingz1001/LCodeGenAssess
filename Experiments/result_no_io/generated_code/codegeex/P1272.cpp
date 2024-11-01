#include <stdio.h>
#include <stdlib.h>

#define MAXN 151

int N, P;
int parent[MAXN];
int subtree_size[MAXN];
int dp[MAXN][MAXN];

void dfs(int node) {
    subtree_size[node] = 1;
    for (int i = 0; i < N; i++) {
        if (parent[i] == node) {
            dfs(i);
            subtree_size[node] += subtree_size[i];
            for (int j = 0; j <= P; j++) {
                for (int k = 0; k <= P; k++) {
                    dp[node][j + k] = (dp[node][j + k] < dp[node][j] + dp[i][k] - subtree_size[i]) ? dp[node][j + k] : dp[node][j] + dp[i][k] - subtree_size[i];
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &N, &P);
    for (int i = 1; i < N; i++) {
        scanf("%d %d", &parent[i], &child);
        child--; // Convert to zero-indexed
        parent[child] = i; // Set the parent of the child
    }
    dfs(0); // Start DFS from the root node (0-indexed)
    printf("%d\n", dp[0][P]);
    return 0;
}