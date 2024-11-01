#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int N = 366666;
const long long INF = 1e18;

int n;
long long max_dist[N];

struct Edge {
    int to, next;
    long long weight;
} edges[N * 4];

int head[N], edge_count;

void add_edge(int from, int to, long long weight) {
    edges[edge_count] = {to, head[from], weight};
    head[from] = edge_count++;
}

int depth[N], depth_prime[N];
long long dist[N], dist_prime[N];

void dfs(int node, int parent, long long edge_weight) {
    depth[node] = depth[parent] + 1;
    dist[node] = dist[parent] + edge_weight;
    for (int i = head[node]; i != -1; i = edges[i].next) {
        int neighbor = edges[i].to;
        if (neighbor != parent) {
            dfs(neighbor, node, edges[i].weight);
        }
    }
}

void dfs_prime(int node, int parent, long long edge_weight) {
    depth_prime[node] = depth_prime[parent] + 1;
    dist_prime[node] = dist_prime[parent] + edge_weight;
    for (int i = head[node]; i != -1; i = edges[i].next) {
        int neighbor = edges[i].to;
        if (neighbor != parent) {
            dfs_prime(neighbor, node, edges[i].weight);
        }
    }
}

int main() {
    memset(head, -1, sizeof(head));
    edge_count = 0;

    scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        int x, y;
        long long v;
        scanf("%d %d %lld", &x, &y, &v);
        add_edge(x, y, v);
        add_edge(y, x, v);
    }

    dfs(1, 0, 0);

    memset(head, -1, sizeof(head));
    edge_count = 0;

    for (int i = 0; i < n - 1; ++i) {
        int x, y;
        long long v;
        scanf("%d %d %lld", &x, &y, &v);
        add_edge(x, y, v);
        add_edge(y, x, v);
    }

    dfs_prime(1, 0, 0);

    long long max_distance = -INF;
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            int lca = i, lca_prime = j;
            // Find LCA and LCA' in T and T'
            // This part is omitted for brevity

            long long distance = depth[i] + depth[j] - (depth[lca] + depth_prime[lca_prime]);
            max_distance = max(max_distance, distance);
        }
    }

    printf("%lld\n", max_distance);
    return 0;
}