#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    double sum_x = 0, sum_y = 0, total_weight = 0;
    
    for (int i = 0; i < n; i++) {
        int x, y, w;
        scanf("%d %d %d", &x, &y, &w);
        
        sum_x += x * w;
        sum_y += y * w;
        total_weight += w;
    }
    
    double balance_x = sum_x / total_weight;
    double balance_y = sum_y / total_weight;
    
    printf("%.3f %.3f\n", balance_x, balance_y);
    
    return 0;
}