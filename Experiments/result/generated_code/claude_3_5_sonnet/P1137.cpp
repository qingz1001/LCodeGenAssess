#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MAX_M 200005

int N, M;
int head[MAX_N], to[MAX_M], nxt[MAX_M], cnt;
int indegree[MAX_N], dp[MAX_N];

void add_edge(int u, int v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
    indegree[v]++;
}

void topological_sort() {
    int queue[MAX_N], front = 0, rear = 0;
    
    for (int i = 1; i <= N; i++) {
        if (indegree[i] == 0) {
            queue[rear++] = i;
            dp[i] = 1;
        }
    }
    
    while (front < rear) {
        int u = queue[front++];
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            dp[v] = (dp[v] > dp[u] + 1) ? dp[v] : dp[u] + 1;
            if (--indegree[v] == 0) {
                queue[rear++] = v;
            }
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);
    
    for (int i = 0; i < M; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        add_edge(x, y);
    }
    
    topological_sort();
    
    for (int i = 1; i <= N; i++) {
        printf("%d\n", dp[i]);
    }
    
    return 0;
}