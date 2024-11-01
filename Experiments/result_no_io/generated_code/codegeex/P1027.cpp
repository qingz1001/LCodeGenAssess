#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXCITY 105
#define INF 1e9

struct Airport {
    int x, y;
};

struct City {
    Airport airports[4];
    double railPrice;
};

int n, t, A, B;
City cities[MAXCITY];

double dist(Airport a, Airport b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double min(double a, double b) {
    return a < b ? a : b;
}

void solve() {
    int i, j, k;
    double graph[MAXCITY][MAXCITY];
    memset(graph, 0, sizeof(graph));

    // Initialize graph with distances between airports within the same city
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= 3; j++) {
            for (k = j + 1; k <= 3; k++) {
                graph[i][j * 3 + k] = graph[k * 3 + j] = dist(cities[i].airports[j], cities[i].airports[k]) * cities[i].railPrice;
            }
        }
    }

    // Add distances between airports in different cities
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (i != j) {
                for (k = 1; k <= 3; k++) {
                    graph[i][j * 3 + k] = graph[j * 3 + k][i] = dist(cities[i].airports[1], cities[j].airports[k]) * t;
                }
            }
        }
    }

    // Floyd-Warshall algorithm to find the shortest path
    for (k = 1; k <= n; k++) {
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= n; j++) {
                if (i != j && j != k && i != k) {
                    graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
                }
            }
        }
    }

    // Find the minimum cost path
    double minCost = INF;
    for (i = 1; i <= 3; i++) {
        for (j = 1; j <= 3; j++) {
            minCost = min(minCost, graph[A][i] + graph[i][j * 3 + 1] + graph[j * 3 + 1][B]);
        }
    }

    printf("%.1lf\n", minCost);
}

int main() {
    int i, j;
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d%d%d%d", &t, &A, &B, &t);
        for (j = 1; j <= 3; j++) {
            scanf("%d%d", &cities[i].airports[j].x, &cities[i].airports[j].y);
        }
        scanf("%lf", &cities[i].railPrice);
    }
    solve();
    return 0;
}