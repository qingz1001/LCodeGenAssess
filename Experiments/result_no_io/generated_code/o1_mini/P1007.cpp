#include <stdio.h>
#include <stdlib.h>

int main(){
    int L, N;
    scanf("%d", &L);
    scanf("%d", &N);
    if(N == 0){
        printf("0 0\n");
        return 0;
    }
    int pos;
    int min_time = 0;
    int max_time = 0;
    for(int i=0;i<N;i++){
        scanf("%d", &pos);
        int min_exit = pos < (L +1 - pos) ? pos : (L +1 - pos);
        int max_exit = pos > (L +1 - pos) ? pos : (L +1 - pos);
        if(min_exit > min_time){
            min_time = min_exit;
        }
        if(max_exit > max_time){
            max_time = max_exit;
        }
    }
    printf("%d %d\n", min_time, max_time);
}