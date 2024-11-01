#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAXN 150

int n;
int x[MAXN], y[MAXN];
int adj[MAXN][MAXN];
int visited[MAXN];
int dist[MAXN];
int diameter[MAXN];
int group[MAXN];
int group_count;

void bfs(int start) {
    int i, j;
    for (i = 0; i < n; i++) {
        visited[i] = 0;
        dist[i] = 1000000; // Initialize distances to a large value
    }
    int queue[MAXN];
    int front = 0, rear = 0;
    queue[rear++] = start;
    visited[start] = 1;
    dist[start] = 0;
    while (front < rear) {
        int current = queue[front++];
        for (i = 0; i < n; i++) {
            if (adj[current][i] && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
                dist[i] = dist[current] + 1;
            }
        }
    }
    int max_dist = 0;
    for (i = 0; i < n; i++) {
        if (dist[i] > max_dist) {
            max_dist = dist[i];
        }
    }
    diameter[group[start]] = max_dist;
}

void find_groups() {
    int i;
    group_count = 0;
    for (i = 0; i < n; i++) {
        group[i] = -1;
    }
    for (i = 0; i < n; i++) {
        if (group[i] == -1) {
            group_count++;
            bfs(i);
            for (int j = 0; j < n; j++) {
                if (visited[j]) {
                    group[j] = group_count - 1;
                }
            }
        }
    }
}

double calculate_distance(int a, int b) {
    return sqrt((x[a] - x[b]) * (x[a] - x[b]) + (y[a] - y[b]) * (y[a] - y[b]));
}

double calculate_diameter(int a, int b) {
    int i;
    double max_dist = 0;
    for (i = 0; i < n; i++) {
        double dist1 = calculate_distance(a, i);
        double dist2 = calculate_distance(b, i);
        if (dist1 + dist2 > max_dist) {
            max_dist = dist1 + dist2;
        }
    }
    return max_dist;
}

int main() {
    int i, j;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%1d", &adj[i][j]);
        }
    }
    find_groups();
    double min_diameter = 1000000;
    for (i = 0; i < group_count - 1; i++) {
        for (j = 0; j < group_count; j++) {
            if (i != j) {
                for (int a = 0; a < n; a++) {
                    if (group[a] == i) {
                        for (int b = 0; b < n; b++) {
                            if (group[b] == j) {
                                double new_diameter = calculate_diameter(a, b);
                                if (new_diameter < min_diameter) {
                                    min_diameter = new_diameter;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    printf("%.6lf\n", min_diameter);
    return 0;
}