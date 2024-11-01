#include <stdio.h>
#include <stdint.h>

typedef unsigned long long ull;

// Function to compute floor of cube root of m
ull floor_cbrt(ull m){
    ull left = 0, right = 1000000000, ans = 0;
    while(left <= right){
        ull mid = left + (right - left)/2;
        __int128 mid3 = (__int128)mid * mid * mid;
        if(mid3 <= m){
            ans = mid;
            left = mid +1;
        }
        else{
            right = mid -1;
        }
    }
    return ans;
}

// Function to compute the sum for a given m
ull compute_sum(ull m){
    ull cbrt = floor_cbrt(m);
    ull sum =0;
    for(ull k=2; k<=cbrt; k++){
        sum += m / (k * k * k);
    }
    return sum;
}

int main(){
    ull n;
    if(scanf("%llu", &n)!=1){
        return 0;
    }
    ull left =1, right =1000000000000000000ULL, ans = 0xFFFFFFFFFFFFFFFF;
    while(left <= right){
        ull mid = left + (right - left)/2;
        ull s = compute_sum(mid);
        if(s < n){
            left = mid +1;
        }
        else{
            if(s == n && mid < ans){
                ans = mid;
            }
            right = mid -1;
        }
    }
    if(ans != 0xFFFFFFFFFFFFFFFF){
        printf("%llu\n", ans);
    }
    else{
        printf("-1\n");
    }
    return 0;
}