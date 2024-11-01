#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    long long total_full_score = 0, total_actual_score = 0, total_deduction = 0;
    
    for (int i = 0; i < n; ++i) {
        int full_score, actual_score;
        scanf("%d %d", &full_score, &actual_score);
        
        total_full_score += full_score;
        total_actual_score += actual_score;
        total_deduction += full_score - actual_score;
    }
    
    double weighted_full_score = total_full_score * 3;
    double weighted_actual_score = total_actual_score * 2;
    
    double result = (weighted_full_score - weighted_actual_score) / total_deduction;
    
    printf("%.6f\n", result);
    
    return 0;
}