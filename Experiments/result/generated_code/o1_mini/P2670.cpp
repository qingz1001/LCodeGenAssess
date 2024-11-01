#include <stdio.h>

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    char grid[100][101];
    for(int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }
    int dx[8] = {-1,-1,-1,0,0,1,1,1};
    int dy[8] = {-1,0,1,-1,1,-1,0,1};
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(grid[i][j] == '*') {
                putchar('*');
            }
            else{
                int count = 0;
                for(int k = 0; k < 8; k++) {
                    int ni = i + dx[k];
                    int nj = j + dy[k];
                    if(ni >= 0 && ni < n && nj >= 0 && nj < m && grid[ni][nj] == '*') {
                        count++;
                    }
                }
                putchar('0' + count);
            }
        }
        putchar('\n');
    }
    return 0;
}