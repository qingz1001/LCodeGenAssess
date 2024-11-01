#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 1001
#define MAXM 4001
#define MAXK 10001

int n, m, k;
int d_min, d_max;
int x[MAXN], y[MAXN];
int v[MAXK], u[MAXK];
int a[MAXM], b[MAXM], type[MAXM];
int dist[MAXN][MAXN];
int graph[MAXN][MAXN];
int dist1[MAXN][MAXN], dist2[MAXN][MAXN];
int que[MAXN * MAXN], head, tail;
int dist3[MAXK];

void dijkstra(int start, int graph[MAXN][MAXN], int dist[MAXN][MAXN]) {
    for (int i = 1; i <= n; i++) {
        dist[start][i] = INT_MAX;
    }
    dist[start][start] = 0;
    head = 0, tail = 0;
    que[tail++] = start;
    while (head < tail) {
        int u = que[head++];
        for (int v = 1; v <= n; v++) {
            if (graph[u][v] && dist[start][v] > dist[start][u] + 1) {
                dist[start][v] = dist[start][u] + 1;
                que[tail++] = v;
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    scanf("%d%d", &d_min, &d_max);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &x[i], &y[i]);
    }
    scanf("%d", &k);
    for (int i = 1; i <= k; i++) {
        scanf("%d%d", &v[i], &u[i]);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &a[i], &b[i], &type[i]);
    }

    // 计算曼哈顿距离
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dist[i][j] = abs(x[i] - x[j]) + abs(y[i] - y[j]);
        }
    }

    // 构建图
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (dist[i][j] >= d_min && dist[i][j] <= d_max) {
                graph[i][j] = 1;
            }
        }
    }

    // 使用Dijkstra算法计算从每个停顿点到其他停顿点的最短路径
    for (int i = 1; i <= n; i++) {
        dijkstra(i, graph, dist1);
    }

    // 重新构建图，只保留那些可以互相到达的点
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            graph[i][j] = 0;
            if (dist1[i][j] != INT_MAX && dist1[i][j] <= 2) {
                graph[i][j] = 1;
            }
        }
    }

    // 使用Dijkstra算法计算从每个停顿点到其他停顿点的最短路径
    for (int i = 1; i <= n; i++) {
        dijkstra(i, graph, dist2);
    }

    // 计算每个绝招的最短连击耗时
    for (int i = 1; i <= k; i++) {
        dist3[i] = INT_MAX;
        for (int j = 1; j <= n; j++) {
            if (dist1[v[i]][j] != INT_MAX && dist2[u[i]][j] != INT_MAX) {
                dist3[i] = (dist1[v[i]][j] + dist2[u[i]][j] < dist3[i]) ? dist1[v[i]][j] + dist2[u[i]][j] : dist3[i];
            }
        }
    }

    // 输出结果
    for (int i = 1; i <= k; i++) {
        if (dist3[i] == INT_MAX) {
            printf("-1\n");
        } else {
            printf("%d\n", dist3[i]);
        }
    }

    return 0;
}