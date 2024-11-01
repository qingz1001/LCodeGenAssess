#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXN 1005

int n, m;
int degree[MAXN];
bool graph[MAXN][MAXN];
bool visited[MAXN];

void topological_sort() {
    int queue[MAXN];
    int front = 0, rear = 0;
    int level = 0;

    for (int i = 1; i <= n; i++) {
        if (degree[i] == 0) {
            queue[rear++] = i;
        }
    }

    while (front < rear) {
        int size = rear - front;
        level++;
        while (size--) {
            int node = queue[front++];
            for (int i = 1; i <= n; i++) {
                if (graph[node][i]) {
                    degree[i]--;
                    if (degree[i] == 0) {
                        queue[rear++] = i;
                    }
                }
            }
        }
    }

    printf("%d\n", level);
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int s;
        scanf("%d", &s);
        int stations[MAXN];
        for (int j = 0; j < s; j++) {
            scanf("%d", &stations[j]);
        }

        for (int j = 0; j < s - 1; j++) {
            for (int k = stations[j] + 1; k < stations[j + 1]; k++) {
                for (int l = 0; l < s; l++) {
                    if (!graph[k][stations[l]]) {
                        graph[k][stations[l]] = true;
                        degree[stations[l]]++;
                    }
                }
            }
        }
    }

    topological_sort();

    return 0;
}