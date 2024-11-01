#include <stdio.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int n, x, y;
    scanf("%d %d %d", &n, &x, &y);
    
    int total_cost = 0;
    
    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);
        
        int single_ticket_cost = a * x;
        int day_ticket_cost = y;
        
        total_cost += min(single_ticket_cost, day_ticket_cost);
    }
    
    printf("%d\n", total_cost);
    
    return 0;
}