#include <stdio.h>
#include <string.h>

#define MAX_N 26

int n, m;
int graph[MAX_N][MAX_N];
int in_degree[MAX_N];
int visited[MAX_N];
char sequence[MAX_N + 1];

int toposort() {
    int queue[MAX_N], front = 0, rear = 0;
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (in_degree[i] == 0) {
            queue[rear++] = i;
        }
    }

    while (front < rear) {
        if (rear - front > 1) return 0;  // 多个元素入度为0，无法确定唯一顺序
        int u = queue[front++];
        sequence[count++] = u + 'A';
        for (int v = 0; v < n; v++) {
            if (graph[u][v]) {
                if (--in_degree[v] == 0) {
                    queue[rear++] = v;
                }
            }
        }
    }

    return count == n;  // 如果所有节点都被访问，则可以确定唯一顺序
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        char a, b;
        scanf(" %c<%c", &a, &b);
        int u = a - 'A', v = b - 'A';
        if (!graph[u][v]) {
            graph[u][v] = 1;
            in_degree[v]++;
        }

        if (graph[v][u]) {
            printf("Inconsistency found after %d relations.\n", i + 1);
            return 0;
        }

        if (toposort()) {
            printf("Sorted sequence determined after %d relations: %s.\n", i + 1, sequence);
            return 0;
        }
    }

    printf("Sorted sequence cannot be determined.\n");
    return 0;
}