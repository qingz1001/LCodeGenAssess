#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int price;
    int quantity;
} PriceQuantity;

int main() {
    int expected_price;
    scanf("%d", &expected_price);

    int cost, base_quantity;
    scanf("%d %d", &cost, &base_quantity);

    PriceQuantity *pq = NULL;
    int pq_size = 0;
    int max_price = 0;

    while (1) {
        int price, quantity;
        scanf("%d %d", &price, &quantity);
        if (price == -1 && quantity == -1) break;
        if (price > max_price) max_price = price;

        pq_size++;
        pq = realloc(pq, pq_size * sizeof(PriceQuantity));
        pq[pq_size - 1].price = price;
        pq[pq_size - 1].quantity = quantity;
    }

    int decrease_per_price;
    scanf("%d", &decrease_per_price);

    int max_profit = INT_MIN;
    int best_tax_or_subsidy = 0;

    for (int tax_or_subsidy = -100000; tax_or_subsidy <= 100000; tax_or_subsidy++) {
        int current_price = expected_price;
        int current_quantity = 0;

        if (current_price < cost) continue;

        for (int i = 0; i < pq_size - 1; i++) {
            if (current_price >= pq[i].price && current_price <= pq[i + 1].price) {
                int slope = (pq[i + 1].quantity - pq[i].quantity) / (pq[i + 1].price - pq[i].price);
                current_quantity = pq[i].quantity + slope * (current_price - pq[i].price);
                break;
            }
        }

        if (current_quantity == 0) {
            if (current_price > max_price) {
                current_quantity = pq[pq_size - 1].quantity - decrease_per_price * (current_price - max_price);
            } else {
                current_quantity = pq[0].quantity;
            }
        }

        int unit_profit = current_price - cost + tax_or_subsidy;
        int total_profit = unit_profit * current_quantity;

        if (total_profit > max_profit || (total_profit == max_profit && abs(tax_or_subsidy) < abs(best_tax_or_subsidy))) {
            max_profit = total_profit;
            best_tax_or_subsidy = tax_or_subsidy;
        }
    }

    if (max_profit == INT_MIN) {
        printf("NO SOLUTION\n");
    } else {
        printf("%d\n", best_tax_or_subsidy);
    }

    free(pq);
    return 0;
}