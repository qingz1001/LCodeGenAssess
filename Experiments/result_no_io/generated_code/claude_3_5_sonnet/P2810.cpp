#include <stdio.h>
#include <stdlib.h>

long long count_solutions(long long m) {
    long long count = 0;
    for (long long a = 1; a <= m / 15; a++) {
        for (long long k = 2; k <= 4; k++) {
            long long b = a * k;
            if (b > m / 7) break;
            long long c = b * k;
            if (c > m / 3) break;
            long long d = c * k;
            if (d > m) break;
            count++;
        }
    }
    return count;
}

int main() {
    long long n;
    scanf("%lld", &n);

    long long left = 1, right = 1000000000000000LL;
    long long result = -1;

    while (left <= right) {
        long long mid = left + (right - left) / 2;
        long long solutions = count_solutions(mid);

        if (solutions == n) {
            result = mid;
            right = mid - 1;
        } else if (solutions < n) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    printf("%lld\n", result);

    return 0;
}