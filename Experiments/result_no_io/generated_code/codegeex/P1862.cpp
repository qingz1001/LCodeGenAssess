#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int y_max = -10000;
    int y_min = 10000;
    
    for (int i = 0; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        
        if (y > y_max) {
            y_max = y;
        }
        if (y < y_min) {
            y_min = y;
        }
    }
    
    int total_length = 0;
    for (int i = 0; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        
        total_length += (y_max - y_min);
    }
    
    printf("%d\n", total_length);
    
    return 0;
}