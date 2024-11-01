#include <stdio.h>
#include <math.h>

double calculate_rate(int w0, int w, int m) {
    double left = 0, right = 3;
    while (right - left > 1e-7) {
        double mid = (left + right) / 2;
        double sum = w0;
        for (int i = 0; i < m; i++) {
            sum = sum * (1 + mid) - w;
        }
        if (sum > 0) {
            left = mid;
        } else {
            right = mid;
        }
    }
    return left * 100;
}

int main() {
    int w0, w, m;
    scanf("%d %d %d", &w0, &w, &m);
    
    double rate = calculate_rate(w0, w, m);
    printf("%.1f\n", round(rate * 10) / 10);
    
    return 0;
}