#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 3001
#define MAX_R 8000

int n, p, r;
int price[MAX_N];
int graph[MAX_N][MAX_N];
int visited[MAX_N];
int queue[MAX_N];

void bfs(int start) {
    int front = 0, rear = 0;
    queue[rear++] = start;
    visited[start] = 1;

    while (front < rear) {
        int current = queue[front++];
        for (int i = 1; i <= n; i++) {
            if (graph[current][i] && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    scanf("%d", &p);

    memset(price, -1, sizeof(price));
    for (int i = 0; i < p; i++) {
        int spy, cost;
        scanf("%d %d", &spy, &cost);
        price[spy] = cost;
    }

    scanf("%d", &r);
    for (int i = 0; i < r; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        graph[a][b] = 1;
    }

    long long total_cost = 0;
    memset(visited, 0, sizeof(visited));

    for (int i = 1; i <= n; i++) {
        if (price[i] != -1 && !visited[i]) {
            total_cost += price[i];
            bfs(i);
        }
    }

    int all_controlled = 1;
    int first_uncontrolled = -1;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            all_controlled = 0;
            first_uncontrolled = i;
            break;
        }
    }

    if (all_controlled) {
        printf("YES\n%lld\n", total_cost);
    } else {
        printf("NO\n%d\n", first_uncontrolled);
    }

    return 0;
}