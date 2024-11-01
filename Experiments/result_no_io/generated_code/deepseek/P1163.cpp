#include <stdio.h>
#include <math.h>

double calculate_monthly_rate(double w0, double w, int m) {
    double low = 0.0, high = 3.0; // high is 300% as a decimal
    double mid, balance;

    for (int i = 0; i < 100; i++) { // 100 iterations for precision
        mid = (low + high) / 2.0;
        balance = w0;

        for (int j = 0; j < m; j++) {
            balance *= (1 + mid);
            balance -= w;
        }

        if (balance > 0) {
            high = mid;
        } else {
            low = mid;
        }
    }

    return mid * 100; // Convert to percentage
}

int main() {
    int w0, w, m;
    scanf("%d %d %d", &w0, &w, &m);

    double rate = calculate_monthly_rate(w0, w, m);
    printf("%.1f\n", rate);

    return 0;
}