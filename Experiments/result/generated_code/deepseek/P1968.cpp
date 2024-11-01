#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    
    int rates[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &rates[i]);
    }
    
    double max_dollars = 100.0;
    double max_marks = 0.0;
    
    for (int i = 0; i < N; i++) {
        double current_marks = max_dollars * rates[i] / 100.0;
        double current_dollars = max_marks * 100.0 / rates[i];
        
        if (current_marks > max_marks) {
            max_marks = current_marks;
        }
        
        if (current_dollars > max_dollars) {
            max_dollars = current_dollars;
        }
    }
    
    printf("%.2f\n", max_dollars);
    
    return 0;
}