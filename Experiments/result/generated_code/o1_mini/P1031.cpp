#include <stdio.h>

int main(){
    int N;
    scanf("%d", &N);
    int A[N];
    long long sum = 0;
    for(int i=0;i<N;i++){
        scanf("%d", &A[i]);
        sum += A[i];
    }
    if(sum % N != 0){
        printf("-1");
        return 0;
    }
    long long target = sum / N;
    long long diff = 0;
    int moves = 0;
    for(int i=0;i<N-1;i++){
        diff += A[i] - target;
        if(diff !=0){
            moves++;
        }
    }
    printf("%d", moves);
}