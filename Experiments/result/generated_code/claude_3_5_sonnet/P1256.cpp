#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 182
#define MAX_M 182
#define INF 0x3f3f3f3f

int N, M;
int screen[MAX_N][MAX_M];
int dist[MAX_N][MAX_M];

typedef struct {
    int x, y;
} Point;

Point queue[MAX_N * MAX_M];
int front, rear;

void bfs() {
    front = rear = 0;
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (screen[i][j] == 1) {
                queue[rear++] = (Point){i, j};
                dist[i][j] = 0;
            } else {
                dist[i][j] = INF;
            }
        }
    }
    
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    
    while (front < rear) {
        Point curr = queue[front++];
        
        for (int i = 0; i < 4; i++) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];
            
            if (nx >= 0 && nx < N && ny >= 0 && ny < M && dist[nx][ny] > dist[curr.x][curr.y] + 1) {
                dist[nx][ny] = dist[curr.x][curr.y] + 1;
                queue[rear++] = (Point){nx, ny};
            }
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%1d", &screen[i][j]);
        }
    }
    
    bfs();
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d", dist[i][j]);
            if (j < M - 1) printf(" ");
        }
        printf("\n");
    }
    
    return 0;
}