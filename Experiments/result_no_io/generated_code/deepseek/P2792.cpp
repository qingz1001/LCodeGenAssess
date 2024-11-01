#include <stdio.h>
#include <stdlib.h>
#include <float.h>

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

double minCost = DBL_MAX;

void calculateMinCost(int index, double currentCost) {
    if (index == n) {
        if (currentCost < minCost) {
            minCost = currentCost;
        }
        return;
    }

    // Buy the item at its original price
    double cost = items[index].price * items[index].quantity;
    calculateMinCost(index + 1, currentCost + cost);

    // Apply discounts if possible
    for (int i = 0; i < k; i++) {
        if (discounts[i].A == index + 1) {
            double discountedCost = discounts[i].P * items[discounts[i].B - 1].quantity;
            double originalCost = items[discounts[i].B - 1].price * items[discounts[i].B - 1].quantity;
            if (discountedCost < originalCost) {
                double tempPrice = items[discounts[i].B - 1].price;
                items[discounts[i].B - 1].price = discounts[i].P;
                calculateMinCost(index + 1, currentCost + cost);
                items[discounts[i].B - 1].price = tempPrice;
            }
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

    calculateMinCost(0, 0.0);

    printf("%.2lf\n", minCost);

    return 0;
}