#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500
#define EMPTY '.'
#define BLOCK '#'
#define CAPTAIN 'C'
#define DOCTOR 'D'

int n, m;
char grid[MAX_N][MAX_N];
int captain_x, captain_y;
int doctor_x, doctor_y;

void find_positions() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == CAPTAIN) {
                captain_x = i;
                captain_y = j;
            } else if (grid[i][j] == DOCTOR) {
                doctor_x = i;
                doctor_y = j;
            }
        }
    }
}

int bfs(int start_row, int start_col) {
    int visited[MAX_N][MAX_N] = {0};
    int queue[MAX_N * MAX_N][2];
    int front = 0, rear = 0;
    queue[rear][0] = start_row;
    queue[rear++][1] = start_col;
    visited[start_row][start_col] = 1;
    int steps = 0;
    
    while (front != rear) {
        int size = rear - front;
        for (int k = 0; k < size; k++) {
            int x = queue[front][0];
            int y = queue[front++][1];
            
            if (x == doctor_x && y == doctor_y) {
                return steps;
            }
            
            // Check below
            if (x + 1 < n && grid[x + 1][y] != BLOCK && !visited[x + 1][y]) {
                visited[x + 1][y] = 1;
                queue[rear][0] = x + 1;
                queue[rear++][1] = y;
            }
            
            // Check above
            if (x > 0 && grid[x - 1][y] != BLOCK && !visited[x - 1][y]) {
                visited[x - 1][y] = 1;
                queue[rear][0] = x - 1;
                queue[rear++][1] = y;
            }
            
            // Check left
            if (y > 0 && grid[x][y - 1] != BLOCK && !visited[x][y - 1]) {
                visited[x][y - 1] = 1;
                queue[rear][0] = x;
                queue[rear++][1] = y - 1;
            }
            
            // Check right
            if (y + 1 < m && grid[x][y + 1] != BLOCK && !visited[x][y + 1]) {
                visited[x][y + 1] = 1;
                queue[rear][0] = x;
                queue[rear++][1] = y + 1;
            }
        }
        steps++;
    }
    return -1;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf(" %c", &grid[i][j]);
        }
    }
    
    find_positions();
    
    int min_flips = INT_MAX;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == EMPTY || grid[i][j] == CAPTAIN) {
                int result = bfs(i, j);
                if (result != -1) {
                    min_flips = fmin(min_flips, result);
                }
            }
        }
    }
    
    printf("%d\n", min_flips == INT_MAX ? -1 : min_flips);
    return 0;
}