#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#define MAX_N 51
#define MAX_M 1001
#define INF 1e9

struct Edge {
    int to, weight;
    struct Edge* next;
};

struct Edge* graph[MAX_N];
int n, m, q;
double dist[MAX_N];
int cnt[MAX_N];
int vis[MAX_N];

void addEdge(int from, int to, int weight) {
    struct Edge* edge = (struct Edge*)malloc(sizeof(struct Edge));
    edge->to = to;
    edge->weight = weight;
    edge->next = graph[from];
    graph[from] = edge;
}

int spfa(int start, int end, double mid) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        cnt[i] = 0;
        vis[i] = 0;
    }
    
    dist[start] = 0;
    vis[start] = 1;
    
    int queue[MAX_N * MAX_M];
    int front = 0, rear = 0;
    queue[rear++] = start;
    
    while (front != rear) {
        int u = queue[front++];
        vis[u] = 0;
        if (front == MAX_N * MAX_M) front = 0;
        
        for (struct Edge* e = graph[u]; e != NULL; e = e->next) {
            int v = e->to;
            double newDist = dist[u] + e->weight - mid;
            if (newDist < dist[v]) {
                dist[v] = newDist;
                cnt[v] = cnt[u] + 1;
                if (!vis[v]) {
                    vis[v] = 1;
                    queue[rear++] = v;
                    if (rear == MAX_N * MAX_M) rear = 0;
                }
            }
        }
    }
    
    return dist[end] < 0;
}

double findMinDensity(int start, int end) {
    double left = 0, right = 1e5;
    while (right - left > 1e-4) {
        double mid = (left + right) / 2;
        if (spfa(start, end, mid)) {
            right = mid;
        } else {
            left = mid;
        }
    }
    return left;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < m; i++) {
        int a, b, w;
        scanf("%d %d %d", &a, &b, &w);
        addEdge(a, b, w);
    }
    
    scanf("%d", &q);
    
    for (int i = 0; i < q; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        
        double result = findMinDensity(x, y);
        if (result >= INF) {
            printf("OMG!\n");
        } else {
            printf("%.3f\n", result);
        }
    }
    
    return 0;
}