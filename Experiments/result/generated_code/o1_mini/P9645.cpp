#include <stdio.h>
#include <math.h>

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        long long x, y, z;
        scanf("%lld %lld %lld", &x, &y, &z);
        long long s = x + y - z;
        if(s <=0){
            printf("-1\n");
            continue;
        }
        long long max_xz = x > z ? x : z;
        if(s <= max_xz){
            printf("-1\n");
            continue;
        }
        long long limit = sqrt((double)s);
        long long min_k = s;
        for(long long d=1; d<=limit; d++){
            if(s % d ==0){
                if(d > max_xz && d < min_k){
                    min_k = d;
                }
                long long pair = s / d;
                if(pair > max_xz && pair < min_k){
                    min_k = pair;
                }
            }
        }
        if(min_k <= 2000000000){
            printf("%lld\n", min_k);
        }
        else{
            printf("-1\n");
        }
    }
}