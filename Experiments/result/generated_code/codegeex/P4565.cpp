#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <map>
using namespace std;

const int MAXN = 366666;
const long long INF = 1e18;

struct Edge {
    int to, weight;
};

vector<Edge> tree[MAXN], tree_prime[MAXN];
long long depth[MAXN], depth_prime[MAXN];
long long max_distance[MAXN];

void dfs(int node, int parent, long long dist, vector<Edge> *tree, long long *depth) {
    depth[node] = dist;
    for (Edge &edge : tree[node]) {
        if (edge.to != parent) {
            dfs(edge.to, node, dist + edge.weight, tree, depth);
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 1; i < n; ++i) {
        int x, y, v;
        scanf("%d %d %d", &x, &y, &v);
        tree[x].push_back({y, v});
        tree[y].push_back({x, v});
    }

    for (int i = 1; i < n; ++i) {
        int x, y, v;
        scanf("%d %d %d", &x, &y, &v);
        tree_prime[x].push_back({y, v});
        tree_prime[y].push_back({x, v});
    }

    dfs(1, -1, 0, tree, depth);
    dfs(1, -1, 0, tree_prime, depth_prime);

    long long max_val = -INF;
    for (int i = 1; i <= n; ++i) {
        for (Edge &edge : tree[i]) {
            int j = edge.to;
            max_distance[i] = max(max_distance[i], depth[i] + depth[j] - 2 * edge.weight);
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (Edge &edge : tree_prime[i]) {
            int j = edge.to;
            max_val = max(max_val, max_distance[i] + max_distance[j] - 2 * edge.weight);
        }
    }

    printf("%lld\n", max_val);
    return 0;
}