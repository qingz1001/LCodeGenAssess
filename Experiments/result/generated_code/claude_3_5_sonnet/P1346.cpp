#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 101
#define INF 1000000000

int N, A, B;
int graph[MAX_N][MAX_N];
int default_route[MAX_N];
int visited[MAX_N];
int queue[MAX_N * MAX_N];
int switches[MAX_N];

int bfs() {
    int front = 0, rear = 0;
    memset(visited, 0, sizeof(visited));
    memset(switches, -1, sizeof(switches));
    
    queue[rear++] = A;
    visited[A] = 1;
    switches[A] = 0;
    
    while (front < rear) {
        int current = queue[front++];
        
        if (current == B) {
            return switches[B];
        }
        
        for (int i = 1; i <= N; i++) {
            if (graph[current][i]) {
                int switch_count = switches[current];
                if (i != default_route[current]) {
                    switch_count++;
                }
                
                if (!visited[i] || switch_count < switches[i]) {
                    queue[rear++] = i;
                    visited[i] = 1;
                    switches[i] = switch_count;
                }
            }
        }
    }
    
    return -1;
}

int main() {
    scanf("%d %d %d", &N, &A, &B);
    
    for (int i = 1; i <= N; i++) {
        int K;
        scanf("%d", &K);
        
        for (int j = 0; j < K; j++) {
            int destination;
            scanf("%d", &destination);
            graph[i][destination] = 1;
            
            if (j == 0) {
                default_route[i] = destination;
            }
        }
    }
    
    int result = bfs();
    printf("%d\n", result);
    
    return 0;
}