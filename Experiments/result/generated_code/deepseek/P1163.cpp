#include <stdio.h>
#include <math.h>

double calculate_monthly_interest(double w0, double w, int m) {
    double low = 0.0, high = 3.0; // 利率范围从0%到300%
    double mid, balance;

    while (high - low > 0.0001) {
        mid = (low + high) / 2.0;
        balance = w0;

        for (int i = 0; i < m; i++) {
            balance *= (1 + mid);
            balance -= w;
        }

        if (balance > 0) {
            high = mid;
        } else {
            low = mid;
        }
    }

    return mid * 100;
}

int main() {
    int w0, w, m;
    scanf("%d %d %d", &w0, &w, &m);

    double monthly_interest = calculate_monthly_interest(w0, w, m);
    printf("%.1f\n", monthly_interest);

    return 0;
}