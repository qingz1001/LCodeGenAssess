#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 50000
#define MAX_COORD 1001

int grid[MAX_COORD][MAX_COORD];
int visited[MAX_COORD][MAX_COORD];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

typedef struct {
    int x, y;
} Point;

Point queue[MAX_N];
int front, rear;

void enqueue(int x, int y) {
    queue[rear].x = x;
    queue[rear].y = y;
    rear++;
}

Point dequeue() {
    return queue[front++];
}

int bfs(int x0, int y0) {
    memset(visited, 0, sizeof(visited));
    front = rear = 0;
    
    enqueue(x0, y0);
    visited[x0][y0] = 1;
    
    int moved = 0;
    
    while (front < rear) {
        int size = rear - front;
        for (int i = 0; i < size; i++) {
            Point current = dequeue();
            
            if (current.x == 0 && current.y == 0) {
                return moved;
            }
            
            for (int j = 0; j < 4; j++) {
                int nx = current.x + dx[j];
                int ny = current.y + dy[j];
                
                if (nx >= 0 && nx < MAX_COORD && ny >= 0 && ny < MAX_COORD && !visited[nx][ny]) {
                    if (grid[nx][ny]) {
                        moved++;
                    }
                    enqueue(nx, ny);
                    visited[nx][ny] = 1;
                }
            }
        }
    }
    
    return -1;
}

int main() {
    int n, x0, y0;
    scanf("%d %d %d", &n, &x0, &y0);
    
    memset(grid, 0, sizeof(grid));
    
    for (int i = 0; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        grid[x][y] = 1;
    }
    
    int result = bfs(x0, y0);
    printf("%d\n", result);
    
    return 0;
}