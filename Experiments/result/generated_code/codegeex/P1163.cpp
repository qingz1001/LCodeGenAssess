#include <stdio.h>
#include <math.h>

int main() {
    int w0, w, m;
    scanf("%d%d%d", &w0, &w, &m);

    double left = 0.0, right = 300.0;
    while (right - left > 0.0001) {
        double mid = (left + right) / 2.0;
        double total_payment = 0.0;
        for (int i = 0; i < m; i++) {
            total_payment += w / (1.0 + mid / 100.0);
        }
        if (total_payment < w0) {
            left = mid;
        } else {
            right = mid;
        }
    }

    printf("%.1lf\n", left * 100.0);
    return 0;
}