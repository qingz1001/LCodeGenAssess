#include <stdio.h>
#include <stdlib.h>

#define MAX_N 150
#define MAX_M 5000

int parent[MAX_N + 1];
int rank[MAX_N + 1];

void init(int n) {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_sets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    init(n);

    int edges[MAX_M][2];
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &edges[i][0], &edges[i][1]);
    }

    int key_roads[MAX_M][2];
    int count = 0;

    for (int i = 0; i < m; i++) {
        int a = edges[i][0];
        int b = edges[i][1];
        int original_parent_a = find(a);
        int original_parent_b = find(b);

        // Temporarily disconnect the edge
        parent[a] = a;
        parent[b] = b;

        // Check if the graph is still connected
        int all_connected = 1;
        for (int j = 0; j < m; j++) {
            if (i == j) continue;
            if (find(edges[j][0]) != find(edges[j][1])) {
                all_connected = 0;
                break;
            }
        }

        if (!all_connected) {
            key_roads[count][0] = a;
            key_roads[count][1] = b;
            count++;
        }

        // Reconnect the edge
        parent[a] = original_parent_a;
        parent[b] = original_parent_b;
    }

    // Sort key roads by a and then by b
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (key_roads[i][0] > key_roads[j][0] || (key_roads[i][0] == key_roads[j][0] && key_roads[i][1] > key_roads[j][1])) {
                int temp[2];
                temp[0] = key_roads[i][0];
                temp[1] = key_roads[i][1];
                key_roads[i][0] = key_roads[j][0];
                key_roads[i][1] = key_roads[j][1];
                key_roads[j][0] = temp[0];
                key_roads[j][1] = temp[1];
            }
        }
    }

    // Output key roads
    for (int i = 0; i < count; i++) {
        printf("%d %d\n", key_roads[i][0], key_roads[i][1]);
    }

    return 0;
}