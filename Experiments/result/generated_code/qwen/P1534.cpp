#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int unhappy_sum = 0;
    int current_unhappy = 0;
    
    for (int i = 0; i < n; i++) {
        int school_time, extra_class_time;
        scanf("%d %d", &school_time, &extra_class_time);
        
        int total_time = school_time + extra_class_time;
        current_unhappy += total_time - 8;
        if (current_unhappy < 0) {
            current_unhappy = 0;
        }
        
        unhappy_sum += current_unhappy;
    }
    
    printf("%d\n", unhappy_sum);
    
    return 0;
}