#include <stdio.h>

int main(){
    int R, C;
    scanf("%d %d", &R, &C);
    char grid[11][11];
    for(int i=0;i<R;i++) {
        scanf("%s", grid[i]);
    }
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    for(int r=0;r<R;r++){
        for(int c=0;c<C;c++){
            if(grid[r][c] == '.'){
                int count = 0;
                for(int d=0;d<4;d++){
                    int nr = r + dr[d];
                    int nc = c + dc[d];
                    if(nr >=0 && nr < R && nc >=0 && nc < C && grid[nr][nc] == '.') {
                        count++;
                    }
                }
                if(count == 1){
                    printf("1");
                    return 0;
                }
            }
        }
    }
    printf("0");
    return 0;
}