#include <stdio.h>
#include <stdlib.h>

#define MAXN 50005
#define MAXM 100010
#define INF 0x3f3f3f3f

typedef struct {
    int to, next, weight;
} Edge;

Edge edges[MAXM];
int head[MAXN], edgeCount = 0;
int n, m, s, t, k;
int visited[MAXN];

void addEdge(int from, int to, int weight) {
    edges[edgeCount].to = to;
    edges[edgeCount].next = head[from];
    edges[edgeCount].weight = weight;
    head[from] = edgeCount++;
}

int bfs(int start, int end) {
    int queue[MAXN], front = 0, rear = 0;
    int dist[MAXN];
    for (int i = 1; i <= n; ++i) {
        dist[i] = INF;
        visited[i] = 0;
    }
    dist[start] = 0;
    queue[rear++] = start;
    visited[start] = 1;
    
    while (front != rear) {
        int u = queue[front++];
        for (int e = head[u]; e != -1; e = edges[e].next) {
            int v = edges[e].to, w = edges[e].weight;
            if (!visited[v]) {
                visited[v] = 1;
                dist[v] = dist[u] + w;
                if (v == end) return dist[end];
                queue[rear++] = v;
            }
        }
    }
    return INF;
}

int main() {
    scanf("%d %d %d %d %d", &n, &m, &s, &t, &k);
    for (int i = 1; i <= n; ++i) head[i] = -1;
    
    for (int i = 0; i < m; ++i) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        addEdge(x, y, z);
    }
    
    int count = 0;
    int sum = 0;
    for (int i = 0; i < m; ++i) {
        int e = i * 2;
        int u = edges[e].from, v = edges[e].to, w = edges[e].weight;
        edges[e].weight = edges[e + 1].weight = 0;
        
        int newDist = bfs(s, t);
        if (newDist >= INF) {
            sum += w;
            count++;
            printf("%d\n", sum);
        }
        
        edges[e].weight = edges[e + 1].weight = w;
    }
    
    if (count < k) {
        printf("-1\n");
    } else {
        for (int i = count - k + 1; i <= count; ++i) {
            printf("%d\n", getSum(i));
        }
    }
    
    return 0;
}