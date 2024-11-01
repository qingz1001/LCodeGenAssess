#include <stdio.h>

long long findB(long long a, long long c) {
    long long left = c, right = a;
    
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        if (mid / c == a / mid) {
            return mid;
        } else if (mid / c < a / mid) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        long long a, c;
        scanf("%lld %lld", &a, &c);
        
        long long result = findB(a, c);
        printf("%lld\n", result);
    }
    
    return 0;
}