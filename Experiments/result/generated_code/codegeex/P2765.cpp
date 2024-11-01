#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 1000

int n;
int *graph[MAXN];
int *vis[MAXN];
int *que;
int head, tail;
int *dist;
int *pre;
int *path;
int maxBall;

void init() {
    for (int i = 0; i < MAXN; i++) {
        graph[i] = (int*)malloc(sizeof(int) * MAXN);
        vis[i] = (int*)malloc(sizeof(int) * MAXN);
        for (int j = 0; j < MAXN; j++) {
            graph[i][j] = 0;
            vis[i][j] = 0;
        }
    }
    que = (int*)malloc(sizeof(int) * MAXN);
    dist = (int*)malloc(sizeof(int) * MAXN);
    pre = (int*)malloc(sizeof(int) * MAXN);
    path = (int*)malloc(sizeof(int) * MAXN);
}

void addEdge(int u, int v) {
    graph[u][v] = 1;
    graph[v][u] = 1;
}

int isPerfectSquare(int x) {
    int root = (int)sqrt(x);
    return root * root == x;
}

void bfs(int start) {
    head = tail = 0;
    for (int i = 0; i < MAXN; i++) dist[i] = -1;
    dist[start] = 0;
    que[tail++] = start;
    while (head < tail) {
        int u = que[head++];
        for (int v = 1; v < MAXN; v++) {
            if (graph[u][v] && dist[v] == -1) {
                dist[v] = dist[u] + 1;
                pre[v] = u;
                que[tail++] = v;
            }
        }
    }
}

void findLongestPath(int u) {
    for (int v = 1; v < MAXN; v++) {
        if (graph[u][v] && dist[u] == dist[v] + 1) {
            findLongestPath(v);
            path[dist[u]] = u;
            break;
        }
    }
}

int main() {
    scanf("%d", &n);
    init();
    for (int i = 1; i < MAXN; i++) {
        for (int j = i + 1; j < MAXN; j++) {
            if (isPerfectSquare(i + j)) {
                addEdge(i, j);
            }
        }
    }
    for (int i = 1; i < MAXN; i++) {
        bfs(i);
        findLongestPath(i);
        if (dist[MAXN - 1] != -1) {
            maxBall = MAXN - 1;
            break;
        }
    }
    printf("%d\n", maxBall);
    for (int i = 0; i < n; i++) {
        int j = maxBall;
        while (j >= 0 && path[j] != 0) {
            printf("%d ", path[j]);
            j--;
        }
        printf("\n");
    }
    return 0;
}