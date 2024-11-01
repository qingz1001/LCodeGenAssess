#include <stdio.h>

int main(){
    long long N, M;
    scanf("%lld %lld", &N, &M);
    long long count = 1, current_sum = 0, num;
    for(long long i = 0; i < N; i++){
        scanf("%lld", &num);
        if(current_sum + num > M){
            count++;
            current_sum = num;
        }
        else{
            current_sum += num;
        }
    }
    printf("%lld\n", count);
    return 0;
}