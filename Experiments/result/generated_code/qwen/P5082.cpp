#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int max_score[n];
    int actual_score[n];
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &max_score[i]);
    }
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &actual_score[i]);
    }
    
    double total_max_score = 0;
    double total_actual_score = 0;
    double total_deduction = 0;
    
    for (int i = 0; i < n; i++) {
        total_max_score += max_score[i] * 3;
        total_actual_score += actual_score[i] * 2;
        total_deduction += max_score[i];
    }
    
    double final_score = (total_max_score - total_actual_score) / total_deduction;
    
    printf("%.6f\n", final_score);
    
    return 0;
}