#include <stdio.h>
#include <math.h>

double g(long long n) {
    double count = 0;
    for (int k = 2; pow(k, 2) <= n; ++k) {
        long long power = k * k;
        while (power <= n) {
            if (power == n) {
                count += 1 / power;
            }
            power *= k;
        }
    }
    return count;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long n;
        scanf("%lld", &n);
        printf("%.14f\n", g(n));
    }
    return 0;
}