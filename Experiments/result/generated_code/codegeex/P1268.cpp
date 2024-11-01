#include <stdio.h>
#include <stdlib.h>

#define MAXN 30
#define INF 100

int n;
int m[MAXN][MAXN];

// 比较函数，用于qsort排序
int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// 计算树的重量
int calculateTreeWeight() {
    int weight = 0;
    int minEdge[MAXN];
    int visited[MAXN] = {0};

    // 遍历所有节点
    for (int i = 0; i < n; i++) {
        int min = INF;
        int minIndex = -1;

        // 找到未访问的节点中，连接到已访问节点的最小边
        for (int j = 0; j < n; j++) {
            if (!visited[j] && m[i][j] < min) {
                min = m[i][j];
                minIndex = j;
            }
        }

        // 将该节点标记为已访问
        visited[minIndex] = 1;

        // 将该边的权值加到总重量中
        weight += min;

        // 更新相邻节点的距离
        for (int j = 0; j < n; j++) {
            if (!visited[j] && m[i][j] > m[minIndex][j]) {
                m[i][j] = m[minIndex][j];
            }
        }
    }

    return weight;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            scanf("%d", &m[i][j]);
            m[j][i] = m[i][j];
        }
    }

    int weight = calculateTreeWeight();
    printf("%d\n", weight);

    return 0;
}