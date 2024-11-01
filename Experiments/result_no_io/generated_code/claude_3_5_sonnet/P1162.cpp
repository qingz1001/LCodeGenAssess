#include <stdio.h>
#include <stdbool.h>

#define MAX_N 30

int n;
int matrix[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool is_valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n;
}

bool can_reach_boundary(int x, int y) {
    if (x == 0 || x == n - 1 || y == 0 || y == n - 1) {
        return true;
    }
    
    visited[x][y] = true;
    
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        
        if (is_valid(nx, ny) && matrix[nx][ny] == 0 && !visited[nx][ny]) {
            if (can_reach_boundary(nx, ny)) {
                return true;
            }
        }
    }
    
    return false;
}

void fill_enclosed_area() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 0) {
                for (int k = 0; k < n; k++) {
                    for (int l = 0; l < n; l++) {
                        visited[k][l] = false;
                    }
                }
                
                if (!can_reach_boundary(i, j)) {
                    matrix[i][j] = 2;
                }
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    
    fill_enclosed_area();
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}