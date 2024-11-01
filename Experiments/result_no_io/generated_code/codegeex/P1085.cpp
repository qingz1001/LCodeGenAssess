#include <stdio.h>

int main() {
    int school_hours[7], extra_hours[7], total_hours[7], max_hours = 0, max_day = 0;
    
    for (int i = 0; i < 7; i++) {
        scanf("%d %d", &school_hours[i], &extra_hours[i]);
        total_hours[i] = school_hours[i] + extra_hours[i];
        if (total_hours[i] > 8 && total_hours[i] > max_hours) {
            max_hours = total_hours[i];
            max_day = i + 1;
        }
    }
    
    printf("%d\n", max_day);
    
    return 0;
}