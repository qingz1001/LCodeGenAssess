#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

#define MAXN 100005

typedef struct {
    int to, next;
    double len;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edge_count = 0;
double dist[MAXN];
int queue[MAXN], front = 0, rear = 0;
int in_queue[MAXN];

void add_edge(int u, int v, double len) {
    edges[edge_count].to = v;
    edges[edge_count].len = len;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void spfa(int start, int n) {
    for (int i = 1; i <= n; i++) {
        dist[i] = DBL_MAX;
        in_queue[i] = 0;
    }
    dist[start] = 0;
    queue[rear++] = start;
    in_queue[start] = 1;

    while (front != rear) {
        int u = queue[front++];
        if (front == MAXN) front = 0;
        in_queue[u] = 0;

        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].to;
            double len = edges[i].len;
            if (dist[u] + len < dist[v]) {
                dist[v] = dist[u] + len;
                if (!in_queue[v]) {
                    queue[rear++] = v;
                    if (rear == MAXN) rear = 0;
                    in_queue[v] = 1;
                }
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) head[i] = -1;

    for (int i = 0; i < n; i++) {
        int a, b;
        double l;
        scanf("%d %d %lf", &a, &b, &l);
        add_edge(a, b, l);
        add_edge(b, a, l);
    }

    spfa(1, n);

    double max_dist = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] > max_dist) max_dist = dist[i];
    }

    printf("%.1f\n", max_dist);

    return 0;
}