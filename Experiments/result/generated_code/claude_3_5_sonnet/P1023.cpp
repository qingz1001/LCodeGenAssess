#include <stdio.h>
#include <stdlib.h>

#define MAX_PRICES 1000

typedef struct {
    int price;
    int sales;
} PriceSales;

int compare(const void *a, const void *b) {
    return ((PriceSales *)a)->price - ((PriceSales *)b)->price;
}

int main() {
    int expected_price, cost, base_sales, decrease_rate;
    PriceSales prices[MAX_PRICES];
    int price_count = 0;

    scanf("%d", &expected_price);
    scanf("%d %d", &cost, &base_sales);

    while (1) {
        int price, sales;
        scanf("%d %d", &price, &sales);
        if (price == -1 && sales == -1) break;
        prices[price_count].price = price;
        prices[price_count].sales = sales;
        price_count++;
    }

    scanf("%d", &decrease_rate);

    qsort(prices, price_count, sizeof(PriceSales), compare);

    int max_profit = 0;
    int best_subsidy = 0;
    int found_solution = 0;

    for (int subsidy = -10000; subsidy <= 10000; subsidy++) {
        int unit_profit = expected_price - cost + subsidy;
        if (unit_profit <= 0) continue;

        int sales;
        if (expected_price <= prices[0].price) {
            sales = base_sales + (prices[0].sales - base_sales) * (expected_price - cost) / (prices[0].price - cost);
        } else if (expected_price > prices[price_count-1].price) {
            sales = prices[price_count-1].sales - decrease_rate * (expected_price - prices[price_count-1].price);
        } else {
            for (int i = 1; i < price_count; i++) {
                if (prices[i].price >= expected_price) {
                    sales = prices[i-1].sales + (prices[i].sales - prices[i-1].sales) * 
                            (expected_price - prices[i-1].price) / (prices[i].price - prices[i-1].price);
                    break;
                }
            }
        }

        int profit = unit_profit * sales;
        if (profit > max_profit) {
            max_profit = profit;
            best_subsidy = subsidy;
            found_solution = 1;
        } else if (profit == max_profit && abs(subsidy) < abs(best_subsidy)) {
            best_subsidy = subsidy;
        }
    }

    for (int i = 0; i < price_count; i++) {
        int unit_profit = prices[i].price - cost;
        int profit = unit_profit * prices[i].sales;
        if (profit > max_profit) {
            found_solution = 0;
            break;
        }
    }

    if (found_solution) {
        printf("%d\n", best_subsidy);
    } else {
        printf("NO SOLUTION\n");
    }

    return 0;
}