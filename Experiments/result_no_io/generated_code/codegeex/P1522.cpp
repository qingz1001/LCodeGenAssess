#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 150

int N;
int X[MAXN], Y[MAXN];
int adj[MAXN][MAXN];
int visited[MAXN];
int dist[MAXN];
int diameter[MAXN];
int group[MAXN];

void dfs(int u, int group_id) {
    visited[u] = 1;
    group[u] = group_id;
    for (int v = 0; v < N; v++) {
        if (adj[u][v] && !visited[v]) {
            dfs(v, group_id);
        }
    }
}

void bfs(int start) {
    for (int i = 0; i < N; i++) {
        dist[i] = -1;
    }
    dist[start] = 0;
    int queue[N];
    int front = 0, rear = 0;
    queue[rear++] = start;
    while (front < rear) {
        int u = queue[front++];
        for (int v = 0; v < N; v++) {
            if (adj[u][v] && dist[v] == -1) {
                dist[v] = dist[u] + 1;
                queue[rear++] = v;
            }
        }
    }
}

double calculate_distance(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &X[i], &Y[i]);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &adj[i][j]);
        }
    }

    int group_id = 0;
    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            dfs(i, group_id++);
        }
    }

    for (int i = 0; i < N; i++) {
        bfs(i);
        for (int j = 0; j < N; j++) {
            diameter[group[i]] = fmax(diameter[group[i]], dist[j]);
        }
    }

    double min_diameter = INFINITY;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (group[i] != group[j]) {
                double new_diameter = fmax(diameter[group[i]], diameter[group[j]]);
                for (int k = 0; k < N; k++) {
                    if (group[k] == group[i] || group[k] == group[j]) {
                        new_diameter = fmax(new_diameter, calculate_distance(X[i], Y[i], X[k], Y[k]) + calculate_distance(X[j], Y[j], X[k], Y[k]));
                    }
                }
                min_diameter = fmin(min_diameter, new_diameter);
            }
        }
    }

    printf("%.6lf\n", min_diameter);
    return 0;
}