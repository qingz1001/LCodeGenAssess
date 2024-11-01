#include <stdio.h>
#include <string.h>

#define MAX 100

int main(){
    int n;
    scanf("%d", &n);
    char grid[MAX][MAX+1];
    for(int i=0;i<n;i++) {
        scanf("%s", grid[i]);
    }
    int mark[MAX][MAX];
    memset(mark, 0, sizeof(mark));
    char word[] = "yizhong";
    int len = strlen(word);
    int dirs[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},          {0, 1},
        {1, -1},  {1,0},  {1,1}
    };
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            for(int d=0; d<8; d++) {
                int ni = i, nj = j;
                int k;
                for(k=0; k<len; k++) {
                    if(ni <0 || ni >=n || nj <0 || nj >=n) break;
                    if(grid[ni][nj] != word[k]) break;
                    ni += dirs[d][0];
                    nj += dirs[d][1];
                }
                if(k == len){
                    ni = i;
                    nj = j;
                    for(k=0; k<len; k++){
                        mark[ni][nj] = 1;
                        ni += dirs[d][0];
                        nj += dirs[d][1];
                    }
                }
            }
        }
    }
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            if(mark[i][j]) printf("%c", grid[i][j]);
            else printf("*");
        }
        printf("\n");
    }
    return 0;
}