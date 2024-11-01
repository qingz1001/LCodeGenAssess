#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int school_hours, extra_hours;
    int total_unhappy = 0;
    int unhappy_level = 0;
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &school_hours, &extra_hours);
        int total_hours = school_hours + extra_hours;
        
        if (total_hours > 8) {
            unhappy_level += total_hours - 8;
        }
        
        total_unhappy += unhappy_level;
    }
    
    printf("%d\n", total_unhappy);
    
    return 0;
}