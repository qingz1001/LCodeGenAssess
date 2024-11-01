#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 400
#define MAX_M 400

int n, m, x, y;
int board[MAX_N][MAX_M];
int queue[MAX_N * MAX_M][2];
int front, rear;

int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};

void bfs(int startX, int startY) {
    memset(board, -1, sizeof(board));
    front = rear = 0;
    
    queue[rear][0] = startX;
    queue[rear][1] = startY;
    rear++;
    board[startX][startY] = 0;
    
    while (front < rear) {
        int x = queue[front][0];
        int y = queue[front][1];
        front++;
        
        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && board[nx][ny] == -1) {
                board[nx][ny] = board[x][y] + 1;
                queue[rear][0] = nx;
                queue[rear][1] = ny;
                rear++;
            }
        }
    }
}

int main() {
    scanf("%d %d %d %d", &n, &m, &x, &y);
    
    bfs(x - 1, y - 1);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}