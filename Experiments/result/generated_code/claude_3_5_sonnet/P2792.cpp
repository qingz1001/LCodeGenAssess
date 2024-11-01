#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#define MAX_N 50
#define MAX_K 500

typedef struct {
    double price;
    int needed;
} Item;

typedef struct {
    int A, B;
    double P;
} Discount;

Item items[MAX_N + 1];
Discount discounts[MAX_K + 1];
double dp[1 << MAX_N];
int n, k;

double min(double a, double b) {
    return a < b ? a : b;
}

double solve() {
    int total_state = 1 << n;
    for (int i = 1; i < total_state; i++) {
        dp[i] = DBL_MAX;
    }
    dp[0] = 0;

    for (int state = 0; state < total_state; state++) {
        for (int i = 0; i < n; i++) {
            if ((state & (1 << i)) == 0) {
                int new_state = state | (1 << i);
                double price = items[i].price;

                for (int j = 0; j < k; j++) {
                    if (discounts[j].B == i + 1 && (state & (1 << (discounts[j].A - 1)))) {
                        price = min(price, discounts[j].P);
                    }
                }

                dp[new_state] = min(dp[new_state], dp[state] + price * items[i].needed);
            }
        }
    }

    return dp[total_state - 1];
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf %d", &items[i].price, &items[i].needed);
    }

    scanf("%d", &k);
    for (int i = 0; i < k; i++) {
        scanf("%d %d %lf", &discounts[i].A, &discounts[i].B, &discounts[i].P);
    }

    double result = solve();
    printf("%.2f\n", result);

    return 0;
}