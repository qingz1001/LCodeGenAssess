#include <stdio.h>
#include <stdlib.h>

#define INF 0x3f3f3f3f

int main() {
    int N, p, m, f, n, s;
    scanf("%d", &N);
    int r[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &r[i]);
    }
    scanf("%d%d%d%d%d", &p, &m, &f, &n, &s);

    // 创建图
    int graph[2 * N + 2][2 * N + 2];
    for (int i = 0; i < 2 * N + 2; i++) {
        for (int j = 0; j < 2 * N + 2; j++) {
            graph[i][j] = INF;
        }
    }

    // 设置源点和汇点
    int source = 2 * N;
    int sink = 2 * N + 1;

    // 添加边
    for (int i = 0; i < N; i++) {
        // 从源点到第i天的需求点
        graph[source][i] = r[i];
        // 第i天的需求点到第i+m天的快洗点
        if (i + m < N) {
            graph[i][i + m] = INF;
        }
        // 第i天的需求点到第i+n天的慢洗点
        if (i + n < N) {
            graph[i][i + n] = INF;
        }
        // 第i天的需求点到第i天的保留点
        graph[i][i] = INF;
    }

    // 设置购买新餐巾的边
    for (int i = 0; i < N; i++) {
        graph[source][i + N] = INF;
    }

    // 设置快洗和慢洗的边
    for (int i = 0; i < N; i++) {
        if (i + m < N) {
            graph[i + m][sink] = f;
        }
        if (i + n < N) {
            graph[i + n][sink] = s;
        }
    }

    // 使用最小费用最大流算法求解
    int flow[2 * N + 2][2 * N + 2];
    int cost[2 * N + 2][2 * N + 2];
    int minCost = 0;

    while (1) {
        // 初始化距离数组和前驱数组
        int dist[2 * N + 2];
        int prev[2 * N + 2];
        for (int i = 0; i < 2 * N + 2; i++) {
            dist[i] = INF;
            prev[i] = -1;
        }

        // 使用SPFA算法找到最短路径
        dist[source] = 0;
        int queue[2 * N + 2];
        int front = 0, rear = 0;
        queue[rear++] = source;
        while (front < rear) {
            int u = queue[front++];
            for (int v = 0; v < 2 * N + 2; v++) {
                if (graph[u][v] != INF && dist[u] + cost[u][v] < dist[v]) {
                    dist[v] = dist[u] + cost[u][v];
                    prev[v] = u;
                    queue[rear++] = v;
                    if (rear >= 2 * N + 2) {
                        rear = 0;
                    }
                }
            }
        }

        // 如果没有增广路径，结束算法
        if (dist[sink] == INF) {
            break;
        }

        // 更新流量和费用
        int f = INF;
        for (int v = sink; v != source; v = prev[v]) {
            f = f < graph[prev[v]][v] ? f : graph[prev[v]][v];
        }
        for (int v = sink; v != source; v = prev[v]) {
            graph[v][prev[v]] += f;
            graph[prev[v]][v] -= f;
            minCost += f * cost[prev[v]][v];
        }
    }

    printf("%d\n", minCost);
    return 0;
}