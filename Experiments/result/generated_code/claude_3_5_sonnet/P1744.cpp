#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 100
#define INF 1e9

typedef struct {
    int x, y;
} Point;

Point shops[MAX_N + 1];
double dist[MAX_N + 1][MAX_N + 1];
double shortest[MAX_N + 1];
int visited[MAX_N + 1];

double calculate_distance(Point a, Point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int main() {
    int n, m, s, t;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &shops[i].x, &shops[i].y);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dist[i][j] = INF;
        }
        dist[i][i] = 0;
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        dist[a][b] = dist[b][a] = calculate_distance(shops[a], shops[b]);
    }

    scanf("%d %d", &s, &t);

    for (int i = 1; i <= n; i++) {
        shortest[i] = INF;
        visited[i] = 0;
    }
    shortest[s] = 0;

    for (int i = 1; i <= n; i++) {
        int v = -1;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && (v == -1 || shortest[j] < shortest[v])) {
                v = j;
            }
        }

        visited[v] = 1;

        for (int j = 1; j <= n; j++) {
            if (shortest[v] + dist[v][j] < shortest[j]) {
                shortest[j] = shortest[v] + dist[v][j];
            }
        }
    }

    printf("%.2f\n", shortest[t]);

    return 0;
}