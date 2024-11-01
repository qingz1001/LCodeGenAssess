#include <stdio.h>
#include <math.h>

long long solve(long long n) {
    long long left = 1, right = 1000000000, mid;
    while (left < right) {
        mid = left + (right - left) / 2;
        if (mid * log10(mid) >= n - 1) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    long long n;
    scanf("%lld", &n);
    printf("%lld\n", solve(n));
    return 0;
}