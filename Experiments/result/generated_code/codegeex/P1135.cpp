#include <stdio.h>
#include <limits.h>

#define MAXN 201

int N, A, B;
int K[MAXN];
int dist[MAXN];

int main() {
    // 读取输入
    scanf("%d %d %d", &N, &A, &B);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &K[i]);
    }

    // 初始化距离数组，所有楼层初始距离为无穷大
    for (int i = 1; i <= N; i++) {
        dist[i] = INT_MAX;
    }

    // 从起始楼层开始
    dist[A] = 0;

    // 使用广度优先搜索（BFS）算法
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (dist[j] == i) { // 当前楼层是距离源点i步可达的
                int up = j + K[j];
                int down = j - K[j];
                if (up <= N && dist[up] > dist[j] + 1) {
                    dist[up] = dist[j] + 1;
                }
                if (down >= 1 && dist[down] > dist[j] + 1) {
                    dist[down] = dist[j] + 1;
                }
            }
        }
    }

    // 输出结果
    if (dist[B] == INT_MAX) {
        printf("-1\n");
    } else {
        printf("%d\n", dist[B]);
    }

    return 0;
}