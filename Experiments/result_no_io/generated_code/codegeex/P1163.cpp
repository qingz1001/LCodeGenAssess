#include <stdio.h>

int main() {
    long long w0, w, m;
    scanf("%lld %lld %lld", &w0, &w, &m);

    double left = 0.0, right = 300.0;
    while (right - left > 0.0001) {
        double mid = (left + right) / 2.0;
        double sum = 0.0;
        for (int i = 0; i < m; i++) {
            sum += w0 * mid / 100.0 * (1.0 + mid / 100.0);
            w0 -= w;
        }
        if (sum >= w * m) {
            right = mid;
        } else {
            left = mid;
        }
    }

    printf("%.1lf%%\n", left * 100.0);
    return 0;
}