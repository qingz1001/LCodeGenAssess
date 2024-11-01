#include <stdio.h>

int main(){
    long long N;
    scanf("%lld", &N);
    for(int X=100; X>=1; X--){
        long long rem = N - 364 * X;
        if(rem > 0 && rem % 1092 == 0){
            long long K = rem / 1092;
            printf("%d\n%lld", X, K);
            return 0;
        }
    }
    return 0;
}