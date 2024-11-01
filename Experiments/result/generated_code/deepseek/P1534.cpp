#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int unhappy_sum = 0;
    int unhappy_level = 0;
    
    for (int i = 0; i < n; i++) {
        int school_time, extra_time;
        scanf("%d %d", &school_time, &extra_time);
        
        int total_time = school_time + extra_time;
        unhappy_level += (total_time - 8);
        unhappy_sum += unhappy_level;
    }
    
    printf("%d\n", unhappy_sum);
    
    return 0;
}