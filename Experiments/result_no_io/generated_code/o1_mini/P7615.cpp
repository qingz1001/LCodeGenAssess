#include <stdio.h>

int main(){
    int R, C;
    scanf("%d %d", &R, &C);
    char grid[R][C+1];
    for(int i=0;i<R;i++){
        scanf("%s", grid[i]);
    }
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            if(grid[i][j] == '.'){
                int cnt = 0;
                for(int d=0;d<4;d++){
                    int ni = i + dr[d];
                    int nj = j + dc[d];
                    if(ni >=0 && ni < R && nj >=0 && nj < C){
                        if(grid[ni][nj] == '.') cnt++;
                    }
                }
                if(cnt ==1){
                    printf("1");
                    return 0;
                }
            }
        }
    }
    printf("0");
    return 0;
}