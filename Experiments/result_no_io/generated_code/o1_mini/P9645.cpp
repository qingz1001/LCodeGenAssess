#include <stdio.h>

int main(){
    int T;
    if(scanf("%d", &T)!=1){
        return 0;
    }
    while(T--){
        long long x, y, z;
        if(scanf("%lld %lld %lld", &x, &y, &z)!=3){
            return 0;
        }
        long long d = x + y - z;
        long long m = (x > z) ? x : z;
        if(d > m && d >=1 && d <=2000000000){
            printf("%lld\n", d);
        }
        else{
            printf("-1\n");
        }
    }
    return 0;
}