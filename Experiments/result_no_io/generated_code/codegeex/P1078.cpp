#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 100
#define MAX_K 100
#define INF INT_MAX

int N, K, M, S, T;
int C[MAX_N + 1]; // 文化数组
int A[MAX_K + 1][MAX_K + 1]; // 排斥数组
int adj[MAX_N + 1][MAX_N + 1]; // 邻接矩阵
int dist[MAX_N + 1][1 << MAX_K]; // 最短路径数组

int main() {
    // 初始化
    memset(adj, 0, sizeof(adj));
    memset(dist, 0x3f, sizeof(dist)); // 用0x3f3f3f3f初始化，表示无穷大

    // 输入数据
    scanf("%d%d%d%d%d", &N, &K, &M, &S, &T);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &C[i]);
    }
    for (int i = 1; i <= K; i++) {
        for (int j = 1; j <= K; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    for (int i = 0; i < M; i++) {
        int u, v, d;
        scanf("%d%d%d", &u, &v, &d);
        adj[u][v] = adj[v][u] = d;
    }

    // Dijkstra算法
    dist[S][1 << (C[S] - 1)] = 0; // 起点距离为0
    for (int i = 0; i < (1 << K) - 1; i++) {
        for (int j = 1; j <= N; j++) {
            if (dist[j][i] == INF) continue; // 如果当前节点不可达，跳过
            for (int k = 1; k <= N; k++) {
                if (adj[j][k] == 0) continue; // 如果两个节点之间没有路，跳过
                int new_mask = i | (1 << (C[k] - 1)); // 新的掩码
                if (A[C[k]][C[j]] == 0 && dist[k][new_mask] > dist[j][i] + adj[j][k]) {
                    dist[k][new_mask] = dist[j][i] + adj[j][k]; // 更新最短路径
                }
            }
        }
    }

    // 找到最短路径
    int min_dist = INF;
    for (int i = 0; i < (1 << K); i++) {
        if (dist[T][i] < min_dist) {
            min_dist = dist[T][i];
        }
    }

    // 输出结果
    if (min_dist == INF) {
        printf("-1\n"); // 如果没有找到路径，输出-1
    } else {
        printf("%d\n", min_dist);
    }

    return 0;
}