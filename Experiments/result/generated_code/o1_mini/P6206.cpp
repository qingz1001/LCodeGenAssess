#include <stdio.h>

typedef long long ll;

int main(){
    ll N;
    if(scanf("%lld", &N)!=1){
        return 1;
    }
    ll score = 0;
    while(N !=1){
        if(N % 2){
            N = N * 3 + 1;
        }
        else{
            N = N / 2;
        }
        score++;
    }
    printf("%lld\n", score);
    return 0;
}