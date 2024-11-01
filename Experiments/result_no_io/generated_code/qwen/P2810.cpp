#include <stdio.h>
#include <math.h>

int main() {
    long long n;
    scanf("%lld", &n);

    if (n == 1) {
        printf("1\n");
        return 0;
    }

    for (long long m = 1; ; ++m) {
        long long count = 0;
        for (long long a = 1; a <= m; ++a) {
            for (long long b = a * 2; b <= m; b *= 2) {
                for (long long c = b * 2; c <= m; c *= 2) {
                    for (long long d = c * 2; d <= m; d *= 2) {
                        count++;
                        if (count >= n) {
                            printf("%lld\n", m);
                            return 0;
                        }
                    }
                }
            }
        }
    }

    printf("-1\n");
    return 0;
}