#include <stdio.h>
#include <stdlib.h>

#define MAX_R 51
#define MAX_C 51
#define MAX_N 100

int r, c, n;
int cows[MAX_N][2];
int grid[MAX_R][MAX_C];

int is_safe(int exclude) {
    // Check for each cow
    for(int i = 0; i < n; i++) {
        if(i == exclude) continue;
        int row = cows[i][0];
        int col = cows[i][1];
        int can_escape = 0;
        // Check north
        int blocked = 0;
        for(int k = row - 1; k >= 1; k--) {
            if(grid[k][col]) {
                blocked = 1;
                break;
            }
        }
        if(!blocked) {
            can_escape = 1;
        }
        // Check east
        blocked = 0;
        for(int k = col + 1; k <= c; k++) {
            if(grid[row][k]) {
                blocked = 1;
                break;
            }
        }
        if(!blocked) {
            can_escape = 1;
        }
        if(!can_escape) return 0;
    }
    return 1;
}

int main(){
    scanf("%d %d", &r, &c);
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d %d", &cows[i][0], &cows[i][1]);
        grid[cows[i][0]][cows[i][1]] = 1;
    }
    // Check initial safety
    if(is_safe(-1)){
        printf("0\n");
        return 0;
    }
    // Check removing each cow
    int safe_cows[MAX_N];
    int count = 0;
    for(int i = 0; i < n; i++){
        grid[cows[i][0]][cows[i][1]] = 0;
        if(is_safe(i)){
            safe_cows[count++] = i+1;
        }
        grid[cows[i][0]][cows[i][1]] = 1;
    }
    if(count == 0){
        printf("-1\n");
    }
    else{
        for(int i = 0; i < count; i++) printf("%d\n", safe_cows[i]);
    }
    return 0;
}