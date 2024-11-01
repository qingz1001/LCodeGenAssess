#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 998244353
#define MAXN 300005

int n, m;
int parent[MAXN], depth[MAXN], heavy[MAXN], head[MAXN], subtree_size[MAXN];
int current_index;
int *chain[MAXN], *chain_length;
int *head_edge[MAXN], *head_edge_length;
int *dp[MAXN], *dp_length;

void dfs(int node) {
    subtree_size[node] = 1;
    int max_size = 0;
    for (int i = head_edge[node]; i < head_edge_length[node]; i++) {
        int neighbor = head_edge[i];
        if (neighbor != parent[node]) {
            parent[neighbor] = node;
            depth[neighbor] = depth[node] + 1;
            dfs(neighbor);
            subtree_size[node] += subtree_size[neighbor];
            if (subtree_size[neighbor] > max_size) {
                max_size = subtree_size[neighbor];
                heavy[node] = neighbor;
            }
        }
    }
}

void decompose(int node, int chain_head) {
    heavy[node] = chain_head;
    chain[node] = chain_length[chain_head]++;
    dp[node] = dp_length[chain_head]++;
    for (int i = head_edge[node]; i < head_edge_length[node]; i++) {
        int neighbor = head_edge[i];
        if (neighbor != parent[node] && neighbor != heavy[node]) {
            decompose(neighbor, neighbor);
        }
    }
}

int lca(int u, int v) {
    while (heavy[u] != heavy[v]) {
        if (depth[heavy[u]] > depth[heavy[v]]) {
            u = parent[heavy[u]];
        } else {
            v = parent[heavy[v]];
        }
    }
    return depth[u] < depth[v] ? u : v;
}

int main() {
    scanf("%d %d", &n, &m);
    memset(head, -1, sizeof(head));
    memset(head_edge, -1, sizeof(head_edge));
    memset(chain_length, 0, sizeof(chain_length));
    memset(head_edge_length, 0, sizeof(head_edge_length));
    memset(dp_length, 0, sizeof(dp_length));

    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        head_edge[head_edge_length[u]++] = v;
        head_edge[head_edge_length[v]++] = u;
    }

    dfs(1);
    decompose(1, 1);

    // Initialize dp
    for (int i = 1; i <= n; i++) {
        dp[i][0] = 0;
    }

    // Calculate dp
    for (int i = 1; i <= n; i++) {
        for (int j = head_edge_length[i] - 1; j >= 0; j--) {
            int neighbor = head_edge[i][j];
            if (neighbor != parent[i]) {
                for (int k = 0; k < dp_length[neighbor]; k++) {
                    dp[i][k + 1] = (dp[i][k + 1] + dp[neighbor][k]) % MOD;
                }
            }
        }
    }

    long long result = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j) {
                int lca_node = lca(i, j);
                long long max_w = 0;
                for (int k = 0; k < dp_length[i]; k++) {
                    for (int l = 0; l < dp_length[j]; l++) {
                        if (k + l > 0) {
                            max_w = (max_w + dp[i][k] * dp[j][l]) % MOD;
                        }
                    }
                }
                result = (result + max_w) % MOD;
            }
        }
    }

    printf("%lld\n", result);
    return 0;
}