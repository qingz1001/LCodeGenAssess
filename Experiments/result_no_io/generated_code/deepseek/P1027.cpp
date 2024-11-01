#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define MAX_CITIES 100
#define MAX_AIRPORTS 4

typedef struct {
    double x, y;
} Point;

typedef struct {
    Point airports[MAX_AIRPORTS];
    double rail_price;
} City;

double distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void find_fourth_point(Point p1, Point p2, Point p3, Point *p4) {
    double dx1 = p2.x - p1.x, dy1 = p2.y - p1.y;
    double dx2 = p3.x - p1.x, dy2 = p3.y - p1.y;
    double cross = dx1 * dy2 - dy1 * dx2;
    if (cross > 0) {
        *p4 = (Point){p1.x + dx1 + dx2, p1.y + dy1 + dy2};
    } else {
        *p4 = (Point){p1.x + dx1 - dx2, p1.y + dy1 - dy2};
    }
}

double dijkstra(double graph[MAX_CITIES * MAX_AIRPORTS][MAX_CITIES * MAX_AIRPORTS], int start, int end, int num_nodes) {
    double dist[num_nodes];
    int visited[num_nodes];
    for (int i = 0; i < num_nodes; i++) {
        dist[i] = DBL_MAX;
        visited[i] = 0;
    }
    dist[start] = 0;

    for (int count = 0; count < num_nodes - 1; count++) {
        double min_dist = DBL_MAX;
        int min_index = -1;
        for (int v = 0; v < num_nodes; v++) {
            if (!visited[v] && dist[v] <= min_dist) {
                min_dist = dist[v];
                min_index = v;
            }
        }
        if (min_index == -1) break;
        visited[min_index] = 1;

        for (int v = 0; v < num_nodes; v++) {
            if (!visited[v] && graph[min_index][v] && dist[min_index] != DBL_MAX &&
                dist[min_index] + graph[min_index][v] < dist[v]) {
                dist[v] = dist[min_index] + graph[min_index][v];
            }
        }
    }
    return dist[end];
}

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        int S, t, A, B;
        scanf("%d %d %d %d", &S, &t, &A, &B);
        City cities[MAX_CITIES];
        for (int i = 0; i < S; i++) {
            scanf("%lf %lf %lf %lf %lf %lf %lf",
                  &cities[i].airports[0].x, &cities[i].airports[0].y,
                  &cities[i].airports[1].x, &cities[i].airports[1].y,
                  &cities[i].airports[2].x, &cities[i].airports[2].y,
                  &cities[i].rail_price);
            find_fourth_point(cities[i].airports[0], cities[i].airports[1], cities[i].airports[2], &cities[i].airports[3]);
        }

        double graph[MAX_CITIES * MAX_AIRPORTS][MAX_CITIES * MAX_AIRPORTS] = {0};
        for (int i = 0; i < S; i++) {
            for (int j = 0; j < MAX_AIRPORTS; j++) {
                for (int k = 0; k < MAX_AIRPORTS; k++) {
                    if (j != k) {
                        graph[i * MAX_AIRPORTS + j][i * MAX_AIRPORTS + k] = distance(cities[i].airports[j], cities[i].airports[k]) * cities[i].rail_price;
                    }
                }
            }
        }

        for (int i = 0; i < S; i++) {
            for (int j = 0; j < S; j++) {
                if (i != j) {
                    for (int k = 0; k < MAX_AIRPORTS; k++) {
                        for (int l = 0; l < MAX_AIRPORTS; l++) {
                            graph[i * MAX_AIRPORTS + k][j * MAX_AIRPORTS + l] = distance(cities[i].airports[k], cities[j].airports[l]) * t;
                        }
                    }
                }
            }
        }

        double min_cost = DBL_MAX;
        for (int i = 0; i < MAX_AIRPORTS; i++) {
            for (int j = 0; j < MAX_AIRPORTS; j++) {
                double cost = dijkstra(graph, (A - 1) * MAX_AIRPORTS + i, (B - 1) * MAX_AIRPORTS + j, S * MAX_AIRPORTS);
                if (cost < min_cost) {
                    min_cost = cost;
                }
            }
        }

        printf("%.1lf\n", min_cost);
    }
    return 0;
}