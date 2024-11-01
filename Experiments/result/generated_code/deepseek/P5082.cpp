#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int a[n], b[n];
    long long sum_full = 0, sum_score = 0, sum_deduction = 0;
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        sum_full += a[i];
    }
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
        sum_score += b[i];
        sum_deduction += (a[i] - b[i]);
    }
    
    double result = (double)(sum_full * 3 - sum_score * 2) / sum_deduction;
    
    printf("%.6f\n", result);
    
    return 0;
}