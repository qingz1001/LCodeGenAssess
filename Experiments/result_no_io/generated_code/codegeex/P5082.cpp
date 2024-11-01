#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    long long full_score_sum = 0;
    long long actual_score_sum = 0;
    
    for (int i = 0; i < n; i++) {
        long long full_score, actual_score;
        scanf("%lld", &full_score);
        full_score_sum += full_score;
        scanf("%lld", &actual_score);
        actual_score_sum += actual_score;
    }
    
    double result = (full_score_sum * 3.0 - actual_score_sum * 2.0) / (full_score_sum - actual_score_sum);
    printf("%.6f\n", result);
    
    return 0;
}