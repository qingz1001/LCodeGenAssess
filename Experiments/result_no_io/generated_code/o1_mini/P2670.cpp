#include <stdio.h>

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    char grid[n][m+1];
    for(int i=0;i<n;i++) {
        scanf("%s", grid[i]);
    }
    int dirs[8][2] = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(grid[i][j] == '*'){
                printf("*");
            }
            else{
                int count=0;
                for(int d=0; d<8; d++){
                    int ni = i + dirs[d][0];
                    int nj = j + dirs[d][1];
                    if(ni >=0 && ni <n && nj >=0 && nj <m && grid[ni][nj] == '*') count++;
                }
                printf("%d", count);
            }
        }
        printf("\n");
    }
    return 0;
}