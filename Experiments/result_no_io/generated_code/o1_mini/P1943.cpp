#include <stdio.h>
#include <math.h>

int main() {
    long long n;
    scanf("%lld", &n);
    double H_n = 0.0;
    if (n <= 1000000) {
        for (long long i = 1; i <= n; i++) {
            H_n += 1.0 / i;
        }
    } else {
        const double gamma = 0.57721566490153286060651209008240243104215933593992;
        double inv_n = 1.0 / (double)n;
        double inv_n_sq = inv_n * inv_n;
        H_n = log((double)n) + gamma + 0.5 * inv_n - (1.0 / 12.0) * inv_n_sq;
    }
    printf("%.8lf\n", H_n);
    return 0;
}