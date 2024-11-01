#include <stdio.h>
#include <math.h>

int main() {
    long long n;
    scanf("%lld", &n);

    long long x = 1;
    while (1) {
        double logResult = x * log10(x);
        if (logResult >= n - 1) {
            printf("%lld\n", x);
            break;
        }
        x++;
    }

    return 0;
}