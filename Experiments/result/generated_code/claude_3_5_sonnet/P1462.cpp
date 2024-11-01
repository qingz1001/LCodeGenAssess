#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 10005
#define MAX_M 50005

typedef struct {
    int to, cost;
    struct Edge* next;
} Edge;

Edge* graph[MAX_N];
int dist[MAX_N];
int fee[MAX_N];
int n, m, b;

void addEdge(int from, int to, int cost) {
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->to = to;
    e->cost = cost;
    e->next = graph[from];
    graph[from] = e;
}

int bfs(int maxFee) {
    int queue[MAX_N], front = 0, rear = 0;
    memset(dist, 0x3f, sizeof(dist));
    
    if (fee[1] > maxFee) return 0;
    queue[rear++] = 1;
    dist[1] = 0;
    
    while (front < rear) {
        int curr = queue[front++];
        if (curr == n) return 1;
        
        for (Edge* e = graph[curr]; e; e = e->next) {
            int next = e->to;
            if (fee[next] > maxFee) continue;
            if (dist[curr] + e->cost < dist[next] && dist[curr] + e->cost <= b) {
                dist[next] = dist[curr] + e->cost;
                queue[rear++] = next;
            }
        }
    }
    return 0;
}

int main() {
    scanf("%d%d%d", &n, &m, &b);
    
    int maxFee = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &fee[i]);
        if (fee[i] > maxFee) maxFee = fee[i];
    }
    
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        addEdge(a, b, c);
        addEdge(b, a, c);
    }
    
    int left = 0, right = maxFee, ans = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (bfs(mid)) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    if (ans == -1) {
        printf("AFK\n");
    } else {
        printf("%d\n", ans);
    }
    
    return 0;
}