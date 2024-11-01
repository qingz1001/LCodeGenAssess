#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#define MAXN 1005
#define MAXM 5005

typedef struct {
    int to, next;
    double weight;
} Edge;

Edge edges[MAXM];
int head[MAXN], cnt;
double fun[MAXN], dist[MAXN];
int in_queue[MAXN], count[MAXN];

void add_edge(int u, int v, double w) {
    edges[cnt].to = v;
    edges[cnt].weight = w;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

int spfa(int n, double mid) {
    int i, u, v;
    int front = 0, rear = 0;
    int queue[MAXN * MAXN];

    for (i = 1; i <= n; i++) {
        dist[i] = 0;
        in_queue[i] = 1;
        count[i] = 0;
        queue[rear++] = i;
    }

    while (front != rear) {
        u = queue[front++];
        if (front == MAXN * MAXN) front = 0;
        in_queue[u] = 0;

        for (i = head[u]; i != -1; i = edges[i].next) {
            v = edges[i].to;
            if (dist[v] < dist[u] + fun[u] - mid * edges[i].weight) {
                dist[v] = dist[u] + fun[u] - mid * edges[i].weight;
                if (!in_queue[v]) {
                    queue[rear++] = v;
                    if (rear == MAXN * MAXN) rear = 0;
                    in_queue[v] = 1;
                    count[v]++;
                    if (count[v] >= n) return 1;
                }
            }
        }
    }
    return 0;
}

int main() {
    int n, m, i, u, v;
    double w, left = 0, right = 1000, mid;

    scanf("%d %d", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%lf", &fun[i]);
    }

    for (i = 1; i <= n; i++) {
        head[i] = -1;
    }

    for (i = 0; i < m; i++) {
        scanf("%d %d %lf", &u, &v, &w);
        add_edge(u, v, w);
    }

    while (right - left > 1e-4) {
        mid = (left + right) / 2;
        if (spfa(n, mid)) {
            left = mid;
        } else {
            right = mid;
        }
    }

    printf("%.2f\n", left);
    return 0;
}