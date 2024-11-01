#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 201

int N, A, B;
int K[MAX_N];
int dist[MAX_N];
int queue[MAX_N];
int front, rear;

void bfs() {
    memset(dist, -1, sizeof(dist));
    front = rear = 0;
    
    dist[A] = 0;
    queue[rear++] = A;
    
    while (front < rear) {
        int current = queue[front++];
        
        if (current == B) return;
        
        int up = current + K[current];
        int down = current - K[current];
        
        if (up <= N && dist[up] == -1) {
            dist[up] = dist[current] + 1;
            queue[rear++] = up;
        }
        
        if (down >= 1 && dist[down] == -1) {
            dist[down] = dist[current] + 1;
            queue[rear++] = down;
        }
    }
}

int main() {
    scanf("%d %d %d", &N, &A, &B);
    
    for (int i = 1; i <= N; i++) {
        scanf("%d", &K[i]);
    }
    
    bfs();
    
    printf("%d\n", dist[B]);
    
    return 0;
}