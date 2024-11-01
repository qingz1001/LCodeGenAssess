#include <stdio.h>

int main() {
    int budget, remaining = 0, saved = 0;
    
    for (int month = 1; month <= 12; month++) {
        scanf("%d", &budget);
        
        remaining += 300;
        
        if (remaining < budget) {
            printf("-%d\n", month);
            return 0;
        }
        
        remaining -= budget;
        saved += remaining / 100 * 100;
        remaining %= 100;
    }
    
    printf("%d\n", remaining + saved + saved / 5);
    return 0;
}