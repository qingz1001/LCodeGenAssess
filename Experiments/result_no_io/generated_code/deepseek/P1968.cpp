#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    
    int rates[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &rates[i]);
    }
    
    double max_value = 100.0; // 初始金额为100美元
    double current_dollars = 100.0;
    double current_marks = 0.0;
    
    for (int i = 0; i < N; i++) {
        // 计算当天用美元换马克的金额
        double marks_from_dollars = current_dollars * rates[i] / 100.0;
        // 计算当天用马克换美元的金额
        double dollars_from_marks = current_marks * 100.0 / rates[i];
        
        // 更新当前的美元和马克金额
        if (marks_from_dollars > current_marks) {
            current_marks = marks_from_dollars;
            current_dollars = 0.0;
        }
        if (dollars_from_marks > current_dollars) {
            current_dollars = dollars_from_marks;
            current_marks = 0.0;
        }
        
        // 更新最大价值
        if (current_dollars > max_value) {
            max_value = current_dollars;
        }
        if (current_marks * 100.0 / rates[i] > max_value) {
            max_value = current_marks * 100.0 / rates[i];
        }
    }
    
    printf("%.2f\n", max_value);
    
    return 0;
}