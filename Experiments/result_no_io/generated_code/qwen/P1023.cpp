#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int main() {
    int expected_price, cost, base_sales;
    scanf("%d %d %d", &expected_price, &cost, &base_sales);

    int prices[MAX_N], sales[MAX_N];
    int n = 0;
    while (1) {
        scanf("%d %d", &prices[n], &sales[n]);
        if (prices[n] == -1 && sales[n] == -1) break;
        n++;
    }

    int price_change_per_unit;
    scanf("%d", &price_change_per_unit);

    int max_profit = INT_MIN;
    int best_tax_or_subsidy = 0;

    for (int tax_or_subsidy = -MAX_N; tax_or_subsidy <= MAX_N; tax_or_subsidy++) {
        int total_profit = 0;
        for (int i = 0; i < n; i++) {
            int current_price = prices[i];
            int current_sales = sales[i];

            if (current_price > expected_price) {
                current_sales -= (current_price - expected_price) * price_change_per_unit;
                if (current_sales < 0) current_sales = 0;
            } else if (current_price < expected_price) {
                current_sales += (expected_price - current_price) * (tax_or_subsidy / (expected_price - current_price));
                if (current_sales < 0) current_sales = 0;
            }

            int profit_per_item = current_price - cost + tax_or_subsidy;
            total_profit += profit_per_item * current_sales;
        }

        if (total_profit > max_profit) {
            max_profit = total_profit;
            best_tax_or_subsidy = tax_or_subsidy;
        }
    }

    if (max_profit == INT_MIN) {
        printf("NO SOLUTION\n");
    } else {
        printf("%d\n", abs(best_tax_or_subsidy));
    }

    return 0;
}