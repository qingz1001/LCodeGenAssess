#include <stdio.h>

int main(){
    int L, N;
    scanf("%d", &L);
    scanf("%d", &N);
    int pos;
    int min_time = 0, max_time = 0;
    for(int i=0;i<N;i++){
        scanf("%d", &pos);
        int left = pos;
        int right = L +1 - pos;
        int current_min = left < right ? left : right;
        int current_max = left > right ? left : right;
        if(current_min > min_time){
            min_time = current_min;
        }
        if(current_max > max_time){
            max_time = current_max;
        }
    }
    printf("%d %d\n", min_time, max_time);
    return 0;
}