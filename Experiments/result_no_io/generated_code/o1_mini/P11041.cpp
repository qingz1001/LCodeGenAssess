#include <stdio.h>

typedef unsigned long long ull;

int main(){
    ull k = 202420242024;
    ull lcm = 120;
    ull low = 1, high = k * 24;
    ull ans = 0;
    while(low <= high){
        ull mid = low + (high - low)/2;
        ull count = mid/20 + mid/24 - mid/lcm;
        if(count >= k){
            ans = mid;
            high = mid -1;
        }
        else{
            low = mid +1;
        }
    }
    printf("%llu\n", ans);
    return 0;
}