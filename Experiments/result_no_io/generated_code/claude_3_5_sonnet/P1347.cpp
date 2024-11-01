#include <stdio.h>
#include <string.h>

#define MAX_N 26
#define MAX_M 600

int n, m;
int graph[MAX_N][MAX_N];
int in_degree[MAX_N];
int visited[MAX_N];
char result[MAX_N + 1];

int topo_sort(int count) {
    int queue[MAX_N], front = 0, rear = 0;
    int sorted = 0;

    for (int i = 0; i < n; i++) {
        if (in_degree[i] == 0) {
            queue[rear++] = i;
        }
    }

    while (front < rear) {
        if (rear - front > 1) return 0;  // 多个元素入度为0，无法确定顺序

        int u = queue[front++];
        result[sorted++] = u + 'A';

        for (int v = 0; v < n; v++) {
            if (graph[u][v]) {
                if (--in_degree[v] == 0) {
                    queue[rear++] = v;
                }
            }
        }
    }

    if (sorted == n) {
        result[n] = '\0';
        printf("Sorted sequence determined after %d relations: %s.\n", count, result);
        return 1;
    }

    return 0;
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= m; i++) {
        char a, b;
        scanf(" %c<%c", &a, &b);
        int u = a - 'A', v = b - 'A';

        if (graph[u][v] == 0) {
            graph[u][v] = 1;
            in_degree[v]++;
        }

        // 检查是否存在环
        memset(visited, 0, sizeof(visited));
        int cycle = 0;
        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                int curr = j;
                while (curr != -1 && !visited[curr]) {
                    visited[curr] = 1;
                    int next = -1;
                    for (int k = 0; k < n; k++) {
                        if (graph[curr][k]) {
                            next = k;
                            break;
                        }
                    }
                    if (next != -1 && visited[next]) {
                        cycle = 1;
                        break;
                    }
                    curr = next;
                }
                if (cycle) break;
            }
        }

        if (cycle) {
            printf("Inconsistency found after %d relations.\n", i);
            return 0;
        }

        if (topo_sort(i)) return 0;
    }

    printf("Sorted sequence cannot be determined.\n");
    return 0;
}