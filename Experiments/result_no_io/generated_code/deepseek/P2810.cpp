#include <stdio.h>
#include <math.h>

long long count_sequences(long long m) {
    long long count = 0;
    for (long long k = 2; k <= m; k++) {
        long long sum = 1 + k + k * k + k * k * k;
        if (sum > m) break;
        count++;
    }
    return count;
}

long long find_min_m(long long n) {
    long long low = 1, high = 1e15, mid;
    while (low < high) {
        mid = (low + high) / 2;
        if (count_sequences(mid) >= n) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    return (count_sequences(low) == n) ? low : -1;
}

int main() {
    long long n;
    scanf("%lld", &n);
    printf("%lld\n", find_min_m(n));
    return 0;
}