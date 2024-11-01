#include <stdio.h>
#include <math.h>

int main() {
    long long a, b;
    scanf("%lld %lld", &a, &b);

    if (a > b) {
        long long temp = a;
        a = b;
        b = temp;
    }

    double phi = (1 + sqrt(5)) / 2;
    long long k = (long long)((b - a) / phi);

    if (a == k) {
        printf("0\n");
    } else {
        printf("1\n");
    }

    return 0;
}