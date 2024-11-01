#include <stdio.h>
#include <string.h>

#define MAX_N 201
#define INF 0x3f3f3f3f

int N, A, B;
int K[MAX_N];
int visited[MAX_N];
int queue[MAX_N];
int dist[MAX_N];

int bfs() {
    int front = 0, rear = 0;
    memset(visited, 0, sizeof(visited));
    memset(dist, 0x3f, sizeof(dist));
    
    queue[rear++] = A;
    visited[A] = 1;
    dist[A] = 0;
    
    while (front < rear) {
        int cur = queue[front++];
        if (cur == B) return dist[cur];
        
        int up = cur + K[cur];
        int down = cur - K[cur];
        
        if (up <= N && !visited[up]) {
            queue[rear++] = up;
            visited[up] = 1;
            dist[up] = dist[cur] + 1;
        }
        
        if (down >= 1 && !visited[down]) {
            queue[rear++] = down;
            visited[down] = 1;
            dist[down] = dist[cur] + 1;
        }
    }
    
    return -1;
}

int main() {
    scanf("%d %d %d", &N, &A, &B);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &K[i]);
    }
    
    int result = bfs();
    printf("%d\n", result);
    
    return 0;
}