#include <stdio.h>
#include <stdlib.h>

#define MAX_N 301

int n, p;
int graph[MAX_N][MAX_N];
int infected[MAX_N];
int queue[MAX_N];
int front, rear;

void bfs() {
    int i, curr;
    front = rear = 0;
    queue[rear++] = 1;
    infected[1] = 1;

    while (front < rear) {
        curr = queue[front++];
        for (i = 1; i <= n; i++) {
            if (graph[curr][i] && !infected[i]) {
                infected[i] = 1;
                queue[rear++] = i;
            }
        }
    }
}

int count_infected() {
    int i, count = 0;
    for (i = 1; i <= n; i++) {
        if (infected[i]) count++;
    }
    return count;
}

int main() {
    int i, j, a, b;

    scanf("%d %d", &n, &p);

    for (i = 0; i < p; i++) {
        scanf("%d %d", &a, &b);
        graph[a][b] = graph[b][a] = 1;
    }

    bfs();

    printf("%d\n", count_infected());

    return 0;
}