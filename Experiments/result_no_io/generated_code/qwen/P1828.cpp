#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PASTURES 800
#define MAX_ROADS 1450
#define INF 999999999

typedef struct {
    int to;
    int weight;
} Edge;

int n, p, c;
int cows[MAX_PASTURES];
Edge roads[MAX_ROADS * 2];

void add_edge(int from, int to, int weight) {
    static int edge_count = 0;
    roads[edge_count].to = to;
    roads[edge_count].weight = weight;
    edge_count++;
}

int min_distance(int start, int end) {
    int dist[MAX_PASTURES];
    for (int i = 0; i < p; i++) {
        dist[i] = INF;
    }
    dist[start] = 0;
    for (int i = 0; i < p - 1; i++) {
        for (int j = 0; j < c * 2; j++) {
            int u = roads[j].from;
            int v = roads[j].to;
            int w = roads[j].weight;
            if (dist[u] != INF && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
            }
        }
    }
    return dist[end];
}

int main() {
    scanf("%d %d %d", &n, &p, &c);
    for (int i = 0; i < n; i++) {
        scanf("%d", &cows[i]);
    }
    for (int i = 0; i < c; i++) {
        int a, b, d;
        scanf("%d %d %d", &a, &b, &d);
        add_edge(a - 1, b - 1, d);
        add_edge(b - 1, a - 1, d);
    }

    int min_cost = INF;
    for (int i = 0; i < n; i++) {
        int cost = 0;
        for (int j = 0; j < n; j++) {
            cost += min_distance(cows[i], cows[j]);
        }
        if (cost < min_cost) {
            min_cost = cost;
        }
    }

    printf("%d\n", min_cost);

    return 0;
}