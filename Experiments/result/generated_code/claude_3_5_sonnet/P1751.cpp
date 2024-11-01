#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 5001
#define MAX_K 1001

int n, k, h;
int graph[MAX_N][MAX_N];
int dist[MAX_N][MAX_N];
int worm_pos[MAX_K];
int food_pos;
int eaten[MAX_K];
int final_pos[MAX_K];

void dfs(int u, int parent, int root, int d) {
    dist[root][u] = d;
    for (int v = 1; v <= n; v++) {
        if (graph[u][v] && v != parent) {
            dfs(v, u, root, d + 1);
        }
    }
}

void calculate_distances() {
    for (int i = 1; i <= n; i++) {
        dfs(i, 0, i, 0);
    }
}

int compare(const void* a, const void* b) {
    int wa = *(int*)a;
    int wb = *(int*)b;
    if (dist[food_pos][worm_pos[wa]] != dist[food_pos][worm_pos[wb]])
        return dist[food_pos][worm_pos[wa]] - dist[food_pos][worm_pos[wb]];
    return wa - wb;
}

void simulate_round() {
    int order[MAX_K];
    for (int i = 0; i < k; i++) order[i] = i;
    qsort(order, k, sizeof(int), compare);

    int blocked[MAX_N] = {0};
    for (int i = 0; i < k; i++) {
        int w = order[i];
        if (worm_pos[w] == food_pos) {
            eaten[w]++;
            break;
        }
        if (blocked[worm_pos[w]]) continue;

        for (int v = 1; v <= n; v++) {
            if (graph[worm_pos[w]][v] && dist[food_pos][v] < dist[food_pos][worm_pos[w]]) {
                if (blocked[v]) {
                    blocked[worm_pos[w]] = 1;
                    break;
                }
                worm_pos[w] = v;
                if (v == food_pos) {
                    eaten[w]++;
                    break;
                }
                blocked[v] = 1;
                break;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        graph[a][b] = graph[b][a] = 1;
    }

    calculate_distances();

    scanf("%d", &k);
    for (int i = 0; i < k; i++) {
        scanf("%d", &worm_pos[i]);
        final_pos[i] = worm_pos[i];
    }

    scanf("%d", &h);
    for (int i = 0; i < h; i++) {
        scanf("%d", &food_pos);
        simulate_round();
        for (int j = 0; j < k; j++) {
            final_pos[j] = worm_pos[j];
        }
    }

    for (int i = 0; i < k; i++) {
        printf("%d %d\n", final_pos[i], eaten[i]);
    }

    return 0;
}