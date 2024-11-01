#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 50
#define MAXM 1250
#define IMPOSSIBLE "IMP0SSBLE!!"

typedef struct {
    int u, v, w;
} Edge;

int n, m, s, t, k;
Edge edges[MAXM];
int monsters[MAXN][4];
int monster_count[MAXN];
int dist[MAXN][MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void floyd_warshall() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = (i == j) ? 0 : INT_MAX;
        }
    }

    for (int i = 0; i < m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;
        dist[u][v] = dist[v][u] = w;
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] < INT_MAX && dist[k][j] < INT_MAX) {
                    dist[i][j] = min(dist[i][j], max(dist[i][k], dist[k][j]));
                }
            }
        }
    }
}

int is_safe(int time, int room, int monster_index) {
    int T = monster_count[monster_index];
    int pos = monsters[monster_index][time % T];
    return pos != room;
}

int main() {
    scanf("%d %d %d %d %d", &n, &m, &s, &t, &k);
    s--; t--;

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
        edges[i].u--; edges[i].v--;
    }

    int a;
    scanf("%d", &a);
    for (int i = 0; i < a; i++) {
        scanf("%d", &monster_count[i]);
        for (int j = 0; j < monster_count[i]; j++) {
            scanf("%d", &monsters[i][j]);
            monsters[i][j]--;
        }
    }

    floyd_warshall();

    int min_blood = INT_MAX;
    for (int blood = 0; blood <= 1000000; blood++) {
        int current_room = s;
        int current_time = 0;
        int possible = 1;

        while (current_time < k) {
            int next_room = -1;
            for (int i = 0; i < n; i++) {
                if (dist[current_room][i] <= blood) {
                    int safe = 1;
                    for (int j = 0; j < a; j++) {
                        if (!is_safe(current_time + 1, i, j)) {
                            safe = 0;
                            break;
                        }
                    }
                    if (safe) {
                        next_room = i;
                        break;
                    }
                }
            }

            if (next_room == -1) {
                possible = 0;
                break;
            }

            current_room = next_room;
            current_time++;
        }

        if (possible && current_room == t) {
            min_blood = blood;
            break;
        }
    }

    if (min_blood == INT_MAX) {
        printf("%s\n", IMPOSSIBLE);
    } else {
        printf("%d\n", min_blood);
    }

    return 0;
}