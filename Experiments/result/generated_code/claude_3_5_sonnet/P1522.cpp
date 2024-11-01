#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 150
#define INF 1e9

typedef struct {
    int x, y;
} Point;

int N;
Point points[MAX_N];
int adj[MAX_N][MAX_N];
double dist[MAX_N][MAX_N];
double max_dist[MAX_N];
int component[MAX_N];

double calculate_distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void floyd_warshall() {
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

void dfs(int v, int c) {
    component[v] = c;
    for (int i = 0; i < N; i++) {
        if (adj[v][i] && component[i] == -1) {
            dfs(i, c);
        }
    }
}

int main() {
    scanf("%d", &N);
    
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%1d", &adj[i][j]);
            if (i == j) {
                dist[i][j] = 0;
            } else if (adj[i][j]) {
                dist[i][j] = calculate_distance(points[i], points[j]);
            } else {
                dist[i][j] = INF;
            }
        }
    }
    
    floyd_warshall();
    
    for (int i = 0; i < N; i++) {
        component[i] = -1;
    }
    
    int c = 0;
    for (int i = 0; i < N; i++) {
        if (component[i] == -1) {
            dfs(i, c++);
        }
    }
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (dist[i][j] < INF) {
                max_dist[i] = fmax(max_dist[i], dist[i][j]);
            }
        }
    }
    
    double result = INF;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (component[i] != component[j]) {
                double new_diameter = fmax(max_dist[i], max_dist[j]);
                new_diameter = fmax(new_diameter, calculate_distance(points[i], points[j]));
                for (int k = 0; k < N; k++) {
                    if (component[k] == component[i]) {
                        for (int l = 0; l < N; l++) {
                            if (component[l] == component[j]) {
                                new_diameter = fmax(new_diameter, dist[k][i] + calculate_distance(points[i], points[j]) + dist[j][l]);
                            }
                        }
                    }
                }
                result = fmin(result, new_diameter);
            }
        }
    }
    
    printf("%.6f\n", result);
    
    return 0;
}