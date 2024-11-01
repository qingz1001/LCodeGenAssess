#include <stdio.h>
#include <string.h>

#define MAX 50

int main(){
    int R, C;
    scanf("%d %d", &R, &C);
    char map[MAX][MAX+1];
    int start_r = -1, start_c = -1;
    for(int i=0;i<R;i++){
        scanf("%s", map[i]);
        for(int j=0;j<C;j++) if(map[i][j]=='*'){
            start_r = i;
            start_c = j;
            map[i][j] = '.';
        }
    }
    int N;
    scanf("%d", &N);
    char directions[N][10];
    for(int i=0;i<N;i++) scanf("%s", directions[i]);
    int current[MAX][MAX];
    memset(current, 0, sizeof(current));
    current[start_r][start_c] = 1;
    for(int i=0;i<N;i++){
        int dr=0, dc=0;
        if(strcmp(directions[i], "NORTH")==0){ dr=-1; dc=0;}
        else if(strcmp(directions[i], "SOUTH")==0){ dr=1; dc=0;}
        else if(strcmp(directions[i], "WEST")==0){ dr=0; dc=-1;}
        else if(strcmp(directions[i], "EAST")==0){ dr=0; dc=1;}
        int new_pos[MAX][MAX];
        memset(new_pos, 0, sizeof(new_pos));
        for(int r=0;r<R;r++) for(int c=0;c<C;c++) if(current[r][c]){
            int nr = r + dr, nc = c + dc;
            while(nr >=0 && nr < R && nc >=0 && nc < C && map[nr][nc] == '.'){
                new_pos[nr][nc] = 1;
                nr += dr;
                nc += dc;
            }
        }
        memcpy(current, new_pos, sizeof(new_pos));
    }
    char result[MAX][MAX+1];
    for(int r=0;r<R;r++) strcpy(result[r], map[r]);
    for(int r=0;r<R;r++) for(int c=0;c<C;c++) if(current[r][c]) result[r][c] = '*';
    for(int r=0;r<R;r++) printf("%s\n", result[r]);
    return 0;
}