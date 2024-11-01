#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, x, y;
    scanf("%d %d %d", &N, &x, &y);
    
    int *a = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }
    
    int total_cost = 0;
    
    for (int i = 0; i < N; i++) {
        int single_ticket_cost = a[i] * x;
        int daily_ticket_cost = y;
        
        if (single_ticket_cost < daily_ticket_cost) {
            total_cost += single_ticket_cost;
        } else {
            total_cost += daily_ticket_cost;
        }
    }
    
    printf("%d\n", total_cost);
    
    free(a);
    return 0;
}