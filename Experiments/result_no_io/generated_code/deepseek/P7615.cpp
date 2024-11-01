#include <stdio.h>

int main() {
    int R, C;
    scanf("%d %d", &R, &C);
    char map[R][C];
    
    for (int i = 0; i < R; i++) {
        scanf("%s", map[i]);
    }
    
    int dead_end = 0;
    
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (map[i][j] == '.') {
                int count = 0;
                if (i > 0 && map[i-1][j] == '.') count++;
                if (i < R-1 && map[i+1][j] == '.') count++;
                if (j > 0 && map[i][j-1] == '.') count++;
                if (j < C-1 && map[i][j+1] == '.') count++;
                
                if (count == 1) {
                    dead_end = 1;
                    break;
                }
            }
        }
        if (dead_end) break;
    }
    
    printf("%d\n", dead_end);
    
    return 0;
}