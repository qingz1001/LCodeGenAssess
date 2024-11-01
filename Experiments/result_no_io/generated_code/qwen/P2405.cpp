#include <stdio.h>
#include <math.h>

int main() {
    long long m;
    int n;
    scanf("%lld %d", &m, &n);

    int count = 0;
    while (m > 0) {
        if (m >= pow(n, count)) {
            m -= pow(n, count);
        } else {
            count++;
        }
    }

    printf("%d\n", count);
    return 0;
}