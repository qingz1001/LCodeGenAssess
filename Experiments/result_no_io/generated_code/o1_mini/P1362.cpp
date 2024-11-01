#include <stdio.h>
#include <stdint.h>

inline int digit_sum(long long x){
    int sum = 0;
    while(x){
        sum += x % 10;
        x /= 10;
    }
    return sum;
}

int main(){
    long long L, R;
    scanf("%lld %lld", &L, &R);
    int count = 0;
    for(long long x = L; x <= R; x++){
        int s = digit_sum(x);
        if(s > 12) continue;
        long long sq = x * x;
        int s_sq = digit_sum(sq);
        if(s_sq == s * s){
            count++;
        }
    }
    printf("%d\n", count);
    return 0;
}