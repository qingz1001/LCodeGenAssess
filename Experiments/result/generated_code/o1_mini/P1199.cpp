#include <stdio.h>
#include <stdlib.h>

int main(){
    int N;
    scanf("%d", &N);
    long long V;
    long long first_max = -1, second_max = -1;
    for(int i=1;i<N;i++){
        for(int j=0;j<N-i;j++){
            scanf("%lld", &V);
            if(V > first_max){
                second_max = first_max;
                first_max = V;
            }
            else if(V > second_max){
                second_max = V;
            }
        }
    }
    if(second_max != -1){
        printf("1\n%lld\n", second_max);
    }
    else{
        printf("0\n");
    }
    return 0;
}