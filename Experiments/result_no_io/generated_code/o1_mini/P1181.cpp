#include <stdio.h>

int main(){
    int N;
    long long M;
    scanf("%d %lld", &N, &M);
    long long A;
    int count = 1;
    long long current_sum = 0;
    for(int i = 0; i < N; i++){
        scanf("%lld", &A);
        if(current_sum + A > M){
            count++;
            current_sum = A;
        }
        else{
            current_sum += A;
        }
    }
    printf("%d\n", count);
    return 0;
}