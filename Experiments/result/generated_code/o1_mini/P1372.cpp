#include <stdio.h>

int main(){
    long long n, k;
    scanf("%lld %lld", &n, &k);
    long long left =1, right =n, ans=1;
    while(left <= right){
        long long mid = left + (right - left)/2;
        long long count = n / mid;
        if(count >=k){
            if(mid > ans){
                ans = mid;
            }
            left = mid +1;
        }
        else{
            right = mid -1;
        }
    }
    printf("%lld\n", ans);
    return 0;
}