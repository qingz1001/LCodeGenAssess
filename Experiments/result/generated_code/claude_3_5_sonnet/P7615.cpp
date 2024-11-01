#include <stdio.h>

#define MAX_SIZE 10

char map[MAX_SIZE][MAX_SIZE];
int R, C;

int is_dead_end(int r, int c) {
    if (map[r][c] == 'X') return 0;
    
    int count = 0;
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    
    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        
        if (nr >= 0 && nr < R && nc >= 0 && nc < C && map[nr][nc] == '.') {
            count++;
        }
    }
    
    return count == 1;
}

int main() {
    scanf("%d %d", &R, &C);
    
    for (int i = 0; i < R; i++) {
        scanf("%s", map[i]);
    }
    
    int has_dead_end = 0;
    
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (is_dead_end(i, j)) {
                has_dead_end = 1;
                break;
            }
        }
        if (has_dead_end) break;
    }
    
    printf("%d\n", has_dead_end);
    
    return 0;
}