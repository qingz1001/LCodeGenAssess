#include <stdio.h>

int main(){
    long long N;
    scanf("%lld", &N);
    for(int X=100; X>=1; X--){
        long long remainder = N - 364LL * X;
        if(remainder > 0 && remainder % 1092 == 0){
            long long K = remainder / 1092;
            if(K > 0){
                printf("%d\n%lld", X, K);
                return 0;
            }
        }
    }
    return 0;
}