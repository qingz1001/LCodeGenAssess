#include <stdio.h>

int main(){
    int i, j;
    int score, sum;
    int max_sum = -1;
    int winner = 0;
    for(i = 1; i <= 5; i++){
        sum = 0;
        for(j = 0; j < 4; j++){
            scanf("%d", &score);
            sum += score;
        }
        if(sum > max_sum){
            max_sum = sum;
            winner = i;
        }
    }
    printf("%d %d\n", winner, max_sum);
    return 0;
}