#include <stdio.h>
#include <string.h>

#define MAX_R 50
#define MAX_C 50
#define MAX_DIR_LEN 10

int main(){
    int R, C;
    scanf("%d %d", &R, &C);
    char map[MAX_R][MAX_C+1];
    int initial_i = -1, initial_j = -1;
    for(int i=0;i<R;i++) {
        scanf("%s", map[i]);
        for(int j=0;j<C;j++) {
            if(map[i][j] == '*'){
                initial_i = i;
                initial_j = j;
                map[i][j] = '.';
            }
        }
    }
    int N;
    scanf("%d", &N);
    char direction[MAX_DIR_LEN];
    int current[MAX_R][MAX_C] = {0};
    current[initial_i][initial_j] = 1;
    int dy, dx;
    for(int step=0; step<N; step++) {
        scanf("%s", direction);
        if(strcmp(direction, "NORTH") == 0){
            dy = -1;
            dx = 0;
        }
        else if(strcmp(direction, "SOUTH") == 0){
            dy = 1;
            dx = 0;
        }
        else if(strcmp(direction, "WEST") == 0){
            dy = 0;
            dx = -1;
        }
        else if(strcmp(direction, "EAST") == 0){
            dy = 0;
            dx = 1;
        }
        else{
            dy = 0;
            dx = 0;
        }
        int next_set[MAX_R][MAX_C] = {0};
        for(int i=0;i<R;i++) {
            for(int j=0;j<C;j++) {
                if(current[i][j]){
                    int ni = i + dy;
                    int nj = j + dx;
                    while(ni >=0 && ni < R && nj >=0 && nj < C && map[ni][nj] != 'X'){
                        next_set[ni][nj] = 1;
                        ni += dy;
                        nj += dx;
                    }
                }
            }
        }
        // Copy next_set to current
        for(int i=0;i<R;i++) {
            for(int j=0;j<C;j++) {
                current[i][j] = next_set[i][j];
            }
        }
    }
    // Mark '*' on map
    for(int i=0;i<R;i++) {
        for(int j=0;j<C;j++) {
            if(current[i][j]){
                map[i][j] = '*';
            }
        }
    }
    // Print map
    for(int i=0;i<R;i++) {
        printf("%s\n", map[i]);
    }
    return 0;
}