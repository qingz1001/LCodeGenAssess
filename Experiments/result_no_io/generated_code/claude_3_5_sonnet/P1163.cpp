#include <stdio.h>
#include <math.h>

double calculate_rate(int w0, int w, int m) {
    double left = 0, right = 3.0;
    while (right - left > 1e-7) {
        double mid = (left + right) / 2;
        double sum = w * ((1 - pow(1 + mid, -m)) / mid);
        if (sum > w0) {
            right = mid;
        } else {
            left = mid;
        }
    }
    return left;
}

int main() {
    int w0, w, m;
    scanf("%d %d %d", &w0, &w, &m);
    
    double rate = calculate_rate(w0, w, m);
    printf("%.1f%%\n", rate * 100);
    
    return 0;
}