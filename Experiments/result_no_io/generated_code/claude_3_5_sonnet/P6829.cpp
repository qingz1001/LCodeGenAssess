#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200000

int n, k;
int r[MAX_N];
int graph[MAX_N][MAX_N];

void init(int k_, int* r_) {
    k = k_;
    memcpy(r, r_, sizeof(int) * n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < k; j++) {
            int next = (i + j) % n;
            if (j <= r[i]) {
                graph[i][next] = -1;
                graph[next][i] = 1;
            } else {
                graph[i][next] = 1;
                graph[next][i] = -1;
            }
        }
    }
}

int compare_plants(int x, int y) {
    if (graph[x][y] != 0) return graph[x][y];
    
    int* queue = malloc(sizeof(int) * n);
    int* visited = calloc(n, sizeof(int));
    int front = 0, rear = 0;
    
    queue[rear++] = x;
    visited[x] = 1;
    
    while (front < rear) {
        int curr = queue[front++];
        for (int i = 0; i < n; i++) {
            if (graph[curr][i] == 1 && !visited[i]) {
                if (i == y) {
                    free(queue);
                    free(visited);
                    return 1;
                }
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
    
    front = rear = 0;
    memset(visited, 0, sizeof(int) * n);
    
    queue[rear++] = y;
    visited[y] = 1;
    
    while (front < rear) {
        int curr = queue[front++];
        for (int i = 0; i < n; i++) {
            if (graph[curr][i] == 1 && !visited[i]) {
                if (i == x) {
                    free(queue);
                    free(visited);
                    return -1;
                }
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
    
    free(queue);
    free(visited);
    return 0;
}

int main() {
    int q;
    scanf("%d %d %d", &n, &k, &q);
    
    int* r_ = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &r_[i]);
    }
    
    init(k, r_);
    free(r_);
    
    for (int i = 0; i < q; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        printf("%d\n", compare_plants(x, y));
    }
    
    return 0;
}