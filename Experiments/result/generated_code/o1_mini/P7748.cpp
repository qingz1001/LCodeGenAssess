#include<stdio.h>

int main(){
    int K, N;
    scanf("%d", &K);
    scanf("%d", &N);
    int current_holder = K;
    int current_time = 0;
    for(int i=0;i<N;i++){
        int T;
        char C;
        scanf("%d %c", &T, &C);
        if(current_time + T >=210){
            printf("%d\n", current_holder);
            return 0;
        }
        current_time += T;
        if(C == 'T'){
            current_holder = (current_holder %8) +1;
        }
    }
    return 0;
}