#include <stdio.h>
#include <stdlib.h>

#define MAX_N 50
#define MAX_K 500
#define EPS 1e-9

typedef struct {
    double price;
    int quantity;
} Item;

typedef struct {
    int a, b;
    double discount;
} Discount;

double dp[MAX_N][MAX_N];

int main() {
    int n, k;
    scanf("%d", &n);
    Item items[MAX_N];
    for (int i = 0; i < n; ++i) {
        scanf("%lf %d", &items[i].price, &items[i].quantity);
    }
    scanf("%d", &k);
    Discount discounts[MAX_K];
    for (int i = 0; i < k; ++i) {
        scanf("%d %d %lf", &discounts[i].a, &discounts[i].b, &discounts[i].discount);
    }

    // Initialize DP table
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= items[i].quantity; ++j) {
            dp[i][j] = 1e9;
        }
    }
    for (int i = 0; i < n; ++i) {
        dp[i][items[i].quantity] = items[i].price * items[i].quantity;
    }

    // Fill DP table
    for (int i = 0; i < n; ++i) {
        for (int j = items[i].quantity; j >= 0; --j) {
            if (dp[i][j] > EPS) {
                for (int l = 0; l < k; ++l) {
                    if (discounts[l].a == i + 1) {
                        int new_quantity = j + items[discounts[l].b - 1].quantity;
                        dp[discounts[l].b - 1][new_quantity] = fmin(dp[discounts[l].b - 1][new_quantity], dp[i][j] * discounts[l].discount * items[discounts[l].b - 1].quantity);
                    }
                }
            }
        }
    }

    // Find the minimum cost
    double min_cost = 1e9;
    for (int i = 0; i < n; ++i) {
        min_cost = fmin(min_cost, dp[i][items[i].quantity]);
    }

    printf("%.2f\n", min_cost);

    return 0;
}