#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 50000
#define MAX_COORD 1000

int haystacks[MAX_COORD + 1][MAX_COORD + 1];
int visited[MAX_COORD + 1][MAX_COORD + 1];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

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

int is_empty() {
    return front == rear;
}

int bfs(int start_x, int start_y) {
    int count = 0;
    front = rear = 0;
    
    enqueue(start_x, start_y);
    visited[start_x][start_y] = 1;
    
    while (!is_empty()) {
        Point current = dequeue();
        
        if (current.x == 0 && current.y == 0) {
            return count;
        }
        
        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            
            if (nx >= 0 && nx <= MAX_COORD && ny >= 0 && ny <= MAX_COORD && !visited[nx][ny]) {
                if (haystacks[nx][ny]) {
                    count++;
                } else {
                    enqueue(nx, ny);
                }
                visited[nx][ny] = 1;
            }
        }
    }
    
    return -1;  // Should not reach here
}

int main() {
    int n, x0, y0;
    scanf("%d %d %d", &n, &x0, &y0);
    
    memset(haystacks, 0, sizeof(haystacks));
    memset(visited, 0, sizeof(visited));
    
    for (int i = 0; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        haystacks[x][y] = 1;
    }
    
    int result = bfs(x0, y0);
    printf("%d\n", result);
    
    return 0;
}