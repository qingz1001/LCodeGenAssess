#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 101
#define MAX_M 121

int n, m;
int graph[MAX_N][MAX_N];
int indegree[MAX_N];
int time[MAX_N];
int queue[MAX_N];
int visited[MAX_N];

void topological_sort() {
    int front = 0, rear = 0;
    int max_time = 0;

    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            queue[rear++] = i;
            time[i] = 0;
        }
    }

    while (front < rear) {
        int current = queue[front++];
        visited[current] = 1;

        if (time[current] > max_time) {
            max_time = time[current];
        }

        for (int i = 1; i <= n; i++) {
            if (graph[current][i] > 0) {
                indegree[i]--;
                if (time[i] < time[current] + graph[current][i]) {
                    time[i] = time[current] + graph[current][i];
                }
                if (indegree[i] == 0) {
                    queue[rear++] = i;
                }
            }
        }
    }

    printf("%d\n", max_time);
    for (int i = 1; i <= n; i++) {
        if (visited[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    scanf("%d", &n);
    scanf("%d", &m);

    memset(graph, 0, sizeof(graph));
    memset(indegree, 0, sizeof(indegree));
    memset(time, 0, sizeof(time));
    memset(visited, 0, sizeof(visited));

    for (int i = 0; i < m; i++) {
        int start, end, duration;
        scanf("%d %d %d", &start, &end, &duration);
        graph[start][end] = duration;
        indegree[end]++;
    }

    topological_sort();

    return 0;
}