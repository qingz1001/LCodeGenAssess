#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int price;
    int sales;
} PriceSales;

int main() {
    int expected_price, cost, cost_sales;
    scanf("%d", &expected_price);
    scanf("%d %d", &cost, &cost_sales);

    PriceSales *data = malloc(sizeof(PriceSales) * 1000);
    int data_size = 0;

    while (1) {
        int price, sales;
        scanf("%d %d", &price, &sales);
        if (price == -1 && sales == -1) break;
        data[data_size].price = price;
        data[data_size].sales = sales;
        data_size++;
    }

    int decrease_sales;
    scanf("%d", &decrease_sales);

    int max_profit = INT_MIN;
    int best_tax_or_subsidy = 0;

    for (int tax_or_subsidy = -100000; tax_or_subsidy <= 100000; tax_or_subsidy++) {
        int current_price = expected_price + tax_or_subsidy;
        if (current_price < cost) continue;

        int current_sales = 0;
        for (int i = 0; i < data_size; i++) {
            if (current_price == data[i].price) {
                current_sales = data[i].sales;
                break;
            } else if (current_price > data[i].price && current_price < data[i + 1].price) {
                current_sales = data[i].sales + (data[i + 1].sales - data[i].sales) * (current_price - data[i].price) / (data[i + 1].price - data[i].price);
                break;
            }
        }

        if (current_sales == 0) {
            current_sales = data[data_size - 1].sales - decrease_sales * (current_price - data[data_size - 1].price);
        }

        int unit_profit = current_price - cost + tax_or_subsidy;
        int total_profit = unit_profit * current_sales;

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

    free(data);
    return 0;
}