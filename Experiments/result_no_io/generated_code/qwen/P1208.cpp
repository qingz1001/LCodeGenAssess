#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int price;
    int amount;
} Farmer;

int compare(const void *a, const void *b) {
    Farmer *farmerA = (Farmer *)a;
    Farmer *farmerB = (Farmer *)b;
    if (farmerA->price != farmerB->price) {
        return farmerA->price - farmerB->price;
    }
    return farmerA->amount - farmerB->amount;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    Farmer farmers[m];
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &farmers[i].price, &farmers[i].amount);
    }
    
    qsort(farmers, m, sizeof(Farmer), compare);
    
    int totalCost = 0;
    for (int i = 0; i < m && n > 0; i++) {
        int buyAmount = (n >= farmers[i].amount) ? farmers[i].amount : n;
        totalCost += buyAmount * farmers[i].price;
        n -= buyAmount;
    }
    
    printf("%d\n", totalCost);
    
    return 0;
}