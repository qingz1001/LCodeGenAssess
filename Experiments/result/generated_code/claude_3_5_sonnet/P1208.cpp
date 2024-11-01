#include <stdio.h>
#include <stdlib.h>

#define MAX_FARMERS 5000

typedef struct {
    int price;
    int amount;
} Farmer;

int compare(const void *a, const void *b) {
    return ((Farmer*)a)->price - ((Farmer*)b)->price;
}

int main() {
    int n, m;
    Farmer farmers[MAX_FARMERS];
    
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &farmers[i].price, &farmers[i].amount);
    }
    
    qsort(farmers, m, sizeof(Farmer), compare);
    
    int total_cost = 0;
    int milk_bought = 0;
    
    for (int i = 0; i < m && milk_bought < n; i++) {
        int buy = (n - milk_bought < farmers[i].amount) ? (n - milk_bought) : farmers[i].amount;
        total_cost += buy * farmers[i].price;
        milk_bought += buy;
    }
    
    printf("%d\n", total_cost);
    
    return 0;
}