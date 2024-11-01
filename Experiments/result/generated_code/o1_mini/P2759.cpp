#include <stdio.h>
#include <math.h>

long long calculate_digits(long long x) {
    if(x == 0) return 1;
    double log_val = x * log10((double)x);
    return (long long)(floor(log_val)) + 1;
}

int main(){
    long long n;
    scanf("%lld", &n);
    long long left = 1, right = 10000000000LL, answer = right;
    while(left <= right){
        long long mid = left + (right - left) / 2;
        long long digits = calculate_digits(mid);
        if(digits >= n){
            answer = mid;
            right = mid -1;
        }
        else{
            left = mid +1;
        }
    }
    printf("%lld\n", answer);
    return 0;
}