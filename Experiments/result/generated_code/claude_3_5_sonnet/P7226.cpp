#include <stdio.h>
#include <math.h>

int main() {
    int n, q, num, p;
    long long X = 0;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &q);
        num = q / 10;
        p = q % 10;
        X += (long long)pow(num, p);
    }

    printf("%lld\n", X);

    return 0;
}