#include <stdio.h>

int main(){
    long long N;
    scanf("%lld", &N);
    int score = 0;
    while(N != 1){
        if(N % 2)
            N = N * 3 + 1;
        else
            N /= 2;
        score++;
    }
    printf("%d\n", score);
    return 0;
}