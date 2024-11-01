#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 5000
#define MAXK 1000

typedef struct {
    int to;
    int next;
} Edge;

Edge edges[2 * MAXN];
int head[MAXN + 1];
int edge_count = 0;

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

int parent[MAXN + 1];
int depth[MAXN + 1];

void dfs(int node, int par, int dep) {
    parent[node] = par;
    depth[node] = dep;
    for (int i = head[node]; i != -1; i = edges[i].next) {
        int to = edges[i].to;
        if (to != par) {
            dfs(to, node, dep + 1);
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        head[i] = -1;
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }

    int k;
    scanf("%d", &k);

    int worm_positions[MAXK];
    for (int i = 0; i < k; i++) {
        scanf("%d", &worm_positions[i]);
    }

    int h;
    scanf("%d", &h);

    int food_positions[h];
    for (int i = 0; i < h; i++) {
        scanf("%d", &food_positions[i]);
    }

    dfs(1, -1, 0);

    int final_positions[MAXK];
    int eat_counts[MAXK] = {0};

    for (int i = 0; i < k; i++) {
        final_positions[i] = worm_positions[i];
    }

    for (int i = 0; i < h; i++) {
        int food_pos = food_positions[i];
        int closest_worm = -1;
        int min_distance = n + 1;

        for (int j = 0; j < k; j++) {
            int worm_pos = final_positions[j];
            int distance = 0;
            while (worm_pos != food_pos) {
                if (depth[worm_pos] < depth[food_pos]) {
                    food_pos = parent[food_pos];
                } else {
                    worm_pos = parent[worm_pos];
                }
                distance++;
            }

            if (distance < min_distance) {
                min_distance = distance;
                closest_worm = j;
            }
        }

        final_positions[closest_worm] = food_positions[i];
        eat_counts[closest_worm]++;
    }

    for (int i = 0; i < k; i++) {
        printf("%d %d\n", final_positions[i], eat_counts[i]);
    }

    return 0;
}