#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double value;
    double cost;
    double ratio;
} Ingredient;

int compare(const void *a, const void *b) {
    return ((Ingredient *)b)->ratio - ((Ingredient *)a)->ratio > 0 ? 1 : -1;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    Ingredient ingredients[n];
    for (int i = 0; i < n; i++) {
        scanf("%lf", &ingredients[i].value);
        scanf("%lf", &ingredients[i].cost);
        ingredients[i].ratio = ingredients[i].value / ingredients[i].cost;
    }
    
    qsort(ingredients, n, sizeof(Ingredient), compare);
    
    double totalValue = 0, totalCost = 0;
    for (int i = 0; i < m; i++) {
        totalValue += ingredients[i].value;
        totalCost += ingredients[i].cost;
    }
    
    printf("%.3f\n", totalValue / totalCost);
    
    return 0;
}