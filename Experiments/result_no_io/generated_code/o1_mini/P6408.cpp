#include <stdio.h>

int main(){
    int scores[5][4];
    int i, j;
    for(i=0;i<5;i++){
        for(j=0;j<4;j++){
            scanf("%d", &scores[i][j]);
        }
    }
    int max_sum = -1;
    int winner = -1;
    for(i=0;i<5;i++){
        int sum = 0;
        for(j=0;j<4;j++) sum += scores[i][j];
        if(sum > max_sum){
            max_sum = sum;
            winner = i + 1;
        }
    }
    printf("%d %d\n", winner, max_sum);
    return 0;
}