#include <stdio.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    
    double ans = 0.0;
    double l = 0.0, r = 1.0;
    const double eps = 1e-9; // 精度要求
    
    for (int i = 0; i < 100; i++) { // 迭代100次以确保精度
        double mid = (l + r) / 2;
        double sum = mid;
        
        for (int j = 1; j < k; j++) {
            sum = sum * mid / (j + 1) + 1;
        }
        
        if (sum > n) {
            r = mid;
        } else {
            l = mid;
            ans = mid;
        }
    }
    
    printf("%.9lf\n", ans);
    return 0;
}