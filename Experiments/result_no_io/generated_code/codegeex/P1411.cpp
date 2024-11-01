#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int N = 710;
const int M = 1300000;
struct Edge {
    int to, next;
} edges[M];
int head[N], edgeCount;
int n, size[N], dp[N][N], maxScore;

void addEdge(int u, int v) {
    edges[edgeCount].to = v;
    edges[edgeCount].next = head[u];
    head[u] = edgeCount++;
}

void dfs(int node, int parent) {
    size[node] = 1;
    dp[node][0] = 1;  // dp[node][0] 表示以 node 为根的连通块大小为 0 时的最大分数
    dp[node][1] = 1;  // dp[node][1] 表示以 node 为根的连通块大小为 1 时的最大分数
    for (int i = head[node]; i != -1; i = edges[i].next) {
        int neighbor = edges[i].to;
        if (neighbor == parent) continue;
        dfs(neighbor, node);
        for (int j = size[node]; j > 0; j--) {
            for (int k = size[neighbor]; k > 0; k--) {
                dp[node][j + k] = max(dp[node][j + k], dp[node][j] * dp[neighbor][k]);
            }
        }
        size[node] += size[neighbor];
    }
    maxScore = max(maxScore, dp[node][1] * (n - size[node]));
}

int main() {
    scanf("%d", &n);
    memset(head, -1, sizeof(head));
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs(1, -1);
    printf("%d\n", maxScore);
    return 0;
}