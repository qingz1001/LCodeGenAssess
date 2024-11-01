#include <stdio.h>
#include <math.h>

long long n;

int main() {
    scanf("%lld", &n);
    long long ans = -1;
    for (long long i = 2; i <= 50000; i++) {
        long long s = 1;
        long long j = 2;
        while (s < n) {
            s *= j;
            j++;
        }
        if (s == n) {
            ans = i;
            break;
        }
    }
    printf("%lld", ans);
    return 0;
}