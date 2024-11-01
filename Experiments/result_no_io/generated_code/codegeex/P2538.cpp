#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 50
#define INF INT_MAX

int n, m, k;
int r[MAX_N], d[MAX_N];
int castle[MAX_N];
int dist[MAX_N];
bool visited[MAX_N];
int min_dist = INF;

void dfs(int city, int current_dist) {
    if (current_dist >= min_dist) return;
    if (visited[city]) {
        min_dist = current_dist;
        return;
    }
    visited[city] = true;
    dist[city] = current_dist;
    dfs(r[city], current_dist + d[city]);
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", &r[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &d[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d", &castle[i]);
        visited[castle[i]] = true;
        dist[castle[i]] = 0;
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            memset(visited, 0, sizeof(visited));
            dfs(i, 0);
        }
    }

    int max_dist = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            max_dist = max(max_dist, dist[i]);
        }
    }

    printf("%d\n", max_dist);
    return 0;
}