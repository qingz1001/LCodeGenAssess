#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    int n;
    scanf("%d", &n);
    char matrix[n][n+1];
    for(int i=0;i<n;i++) {
        scanf("%s", matrix[i]);
    }
    // Initialize mask
    int mask[n][n];
    memset(mask, 0, sizeof(mask));
    // Define directions: up, down, left, right, and the 4 diagonals
    int directions[8][2] = {
        {-1, 0}, // up
        {1, 0},  // down
        {0, -1}, // left
        {0, 1},  // right
        {-1, -1},// up-left
        {-1, 1}, // up-right
        {1, -1}, // down-left
        {1, 1}   // down-right
    };
    char word[8] = "yizhong";
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int d=0; d<8; d++){
                int dx = directions[d][0];
                int dy = directions[d][1];
                int k;
                for(k=0; k<7; k++){
                    int ni = i + k*dx;
                    int nj = j + k*dy;
                    if(ni <0 || ni >=n || nj <0 || nj >=n){
                        break;
                    }
                    if(tolower(matrix[ni][nj]) != word[k]){
                        break;
                    }
                }
                if(k ==7){
                    for(int m=0; m<7; m++){
                        int ni = i + m*dx;
                        int nj = j + m*dy;
                        mask[ni][nj] =1;
                    }
                }
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(mask[i][j]){
                printf("%c", matrix[i][j]);
            }
            else{
                printf("*");
            }
        }
        printf("\n");
    }
}