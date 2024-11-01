#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 50005
#define MAX_M 50005
#define INF 1000000000

typedef struct Edge {
    int v, w, next;
} Edge;

Edge edges[MAX_M * 2];
int head[MAX_N], dis[MAX_N], cnt[MAX_N];
bool vis[MAX_N];
int n, m, S, T, edgeCount;

void addEdge(int u, int v, int w) {
    edges[edgeCount].v = v;
    edges[edgeCount].w = w;
    edges[edgeCount].next = head[u];
    head[u] = edgeCount++;
}

void spfa() {
    for (int i = 1; i <= n; i++) {
        dis[i] = INF;
        vis[i] = false;
        cnt[i] = 0;
    }
    dis[S] = 0;
    
    int queue[MAX_N], front = 0, rear = 0;
    queue[rear++] = S;
    vis[S] = true;
    
    while (front != rear) {
        int u = queue[front++];
        if (front == MAX_N) front = 0;
        vis[u] = false;
        
        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].v;
            int w = edges[i].w;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;
                if (!vis[v]) {
                    queue[rear++] = v;
                    if (rear == MAX_N) rear = 0;
                    vis[v] = true;
                }
            } else if (dis[v] == dis[u] + w) {
                cnt[v] += cnt[u];
            }
        }
    }
}

int main() {
    scanf("%d%d%d%d", &n, &m, &S, &T);
    
    memset(head, -1, sizeof(head));
    edgeCount = 0;
    
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    
    spfa();
    
    int result = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (i != S && i != T && j != S && j != T) {
                if ((cnt[i] == cnt[T] || cnt[j] == cnt[T]) && 
                    (cnt[i] + cnt[j] == cnt[T])) {
                    result++;
                }
            }
        }
    }
    
    printf("%d\n", result);
    
    return 0;
}