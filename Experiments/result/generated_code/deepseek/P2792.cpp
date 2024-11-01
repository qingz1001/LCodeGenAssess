#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 50
#define MAX_K 500

typedef struct {
    int A, B;
    double P;
} Discount;

typedef struct {
    double price;
    int quantity;
} Item;

int n, k;
Item items[MAX_N];
Discount discounts[MAX_K];

double minCost = INT_MAX;

void calculateCost(int index, double currentCost) {
    if (index == n) {
        if (currentCost < minCost) {
            minCost = currentCost;
        }
        return;
    }

    // Buy the item at its original price
    if (items[index].quantity > 0) {
        double originalCost = items[index].price * items[index].quantity;
        items[index].quantity = 0;
        calculateCost(index + 1, currentCost + originalCost);
        items[index].quantity = items[index].quantity;
    }

    // Apply discounts if possible
    for (int i = 0; i < k; i++) {
        if (discounts[i].A == index + 1 && items[discounts[i].B - 1].quantity > 0) {
            double discountCost = discounts[i].P * items[discounts[i].B - 1].quantity;
            int originalQuantity = items[discounts[i].B - 1].quantity;
            items[discounts[i].B - 1].quantity = 0;
            calculateCost(index + 1, currentCost + discountCost);
            items[discounts[i].B - 1].quantity = originalQuantity;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf %d", &items[i].price, &items[i].quantity);
    }
    scanf("%d", &k);
    for (int i = 0; i < k; i++) {
        scanf("%d %d %lf", &discounts[i].A, &discounts[i].B, &discounts[i].P);
    }

    calculateCost(0, 0.0);

    printf("%.2lf\n", minCost);

    return 0;
}