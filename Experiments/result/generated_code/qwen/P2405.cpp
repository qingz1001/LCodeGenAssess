#include <stdio.h>
#include <stdlib.h>

int min_weights(long long m, int n) {
    if (m == 0) return 0;
    if (n == 1) return m;

    long long power = 1;
    while (power <= m) {
        power *= n;
    }
    power /= n;

    int use_right = min_weights(m - power, n) + 1;
    int use_left = min_weights(m + power, n) + 1;
    int use_neither = min_weights(m, n - 1);

    return use_right < use_left ? (use_right < use_neither ? use_right : use_neither) :
           (use_left < use_neither ? use_left : use_neither);
}

int main() {
    long long m;
    int n;
    scanf("%lld %d", &m, &n);

    printf("%d\n", min_weights(m, n));

    return 0;
}