#include <stdio.h>

int main(){
    long long n, k;
    while(scanf("%lld %lld", &n, &k) == 2){
        long long total = n;
        long long butts = n;
        while(butts >= k){
            long long new_cigs = butts / k;
            total += new_cigs;
            butts = butts % k + new_cigs;
        }
        printf("%lld\n", total);
    }
    return 0;
}