#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

typedef struct {
    int price;
    int sales;
} PriceSales;

int main() {
    int expected_price, cost, base_sales;
    scanf("%d %d %d", &expected_price, &cost, &base_sales);

    PriceSales prices[MAX_N];
    int n = 0;
    while (1) {
        scanf("%d %d", &prices[n].price, &prices[n].sales);
        if (prices[n].price == -1 && prices[n].sales == -1) break;
        n++;
    }

    int reduction_per_unit = 0;
    scanf("%d", &reduction_per_unit);

    int min_cost = INT_MAX;
    for (int subsidy = -100000; subsidy <= 100000; subsidy++) {
        int total_profit = 0;
        int current_sales = base_sales;
        int max_profit = 0;

        for (int i = 0; i < n; i++) {
            int price = prices[i].price;
            int sales = prices[i].sales;
            if (price >= expected_price) {
                current_sales -= reduction_per_unit * (price - expected_price);
                if (current_sales < 0) current_sales = 0;
            }
            int profit = (price - cost + subsidy) * sales;
            total_profit += profit;
            if (profit > max_profit) max_profit = profit;
        }

        int price_diff = abs(expected_price - cost);
        int expected_profit = price_diff * base_sales;
        int actual_profit = max_profit;

        if (actual_profit > expected_profit) {
            int difference = actual_profit - expected_profit;
            if (difference < min_cost) {
                min_cost = difference;
            }
        }
    }

    if (min_cost == INT_MAX) {
        printf("NO SOLUTION\n");
    } else {
        printf("%d\n", min_cost);
    }

    return 0;
}