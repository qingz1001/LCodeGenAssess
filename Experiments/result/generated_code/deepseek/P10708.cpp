#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, x, y;
    scanf("%d %d %d", &N, &x, &y);
    
    int *a = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }
    
    int totalCost = 0;
    
    for (int i = 0; i < N; i++) {
        int singleTicketCost = a[i] * x;
        int dayTicketCost = y;
        
        if (singleTicketCost < dayTicketCost) {
            totalCost += singleTicketCost;
        } else {
            totalCost += dayTicketCost;
        }
    }
    
    printf("%d\n", totalCost);
    
    free(a);
    return 0;
}