#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#define MAX_N 50
#define MAX_K 500

typedef struct {
    double price;
    int quantity;
} Item;

typedef struct {
    int A, B;
    double P;
} Discount;

Item items[MAX_N + 1];
Discount discounts[MAX_K];
double dp[1 << MAX_N];
int n, k;

double min(double a, double b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lf %d", &items[i].price, &items[i].quantity);
    }
    
    scanf("%d", &k);
    for (int i = 0; i < k; i++) {
        scanf("%d %d %lf", &discounts[i].A, &discounts[i].B, &discounts[i].P);
    }

    int full_mask = (1 << n) - 1;
    for (int mask = 0; mask <= full_mask; mask++) {
        dp[mask] = DBL_MAX;
    }
    dp[0] = 0;

    for (int mask = 0; mask <= full_mask; mask++) {
        for (int i = 1; i <= n; i++) {
            if (!(mask & (1 << (i - 1)))) {
                double price = items[i].price;
                for (int j = 0; j < k; j++) {
                    if (discounts[j].B == i && (mask & (1 << (discounts[j].A - 1)))) {
                        price = min(price, discounts[j].P);
                    }
                }
                int new_mask = mask | (1 << (i - 1));
                dp[new_mask] = min(dp[new_mask], dp[mask] + price * items[i].quantity);
            }
        }
    }

    printf("%.2f\n", dp[full_mask]);
    return 0;
}