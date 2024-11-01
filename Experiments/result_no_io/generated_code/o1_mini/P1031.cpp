#include<stdio.h>

int main(){
    int N;
    scanf("%d", &N);
    long long A[N];
    long long total = 0;
    for(int i=0;i<N;i++){
        scanf("%lld", &A[i]);
        total += A[i];
    }
    long long target = total / N;
    long long cumulative = 0;
    int moves = 0;
    for(int i=0;i<N-1;i++){
        cumulative += A[i] - target;
        if(cumulative !=0){
            moves++;
        }
    }
    printf("%d", moves);
    return 0;
}