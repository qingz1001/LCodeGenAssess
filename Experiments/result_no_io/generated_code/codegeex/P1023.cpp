#include <stdio.h>

int main() {
    int price, cost, base_volume, decrease_rate;
    int max_profit = -1, max_profit_tax = 0;

    // Read the expected price from the government
    scanf("%d", &price);

    // Read the cost and base volume
    scanf("%d %d", &cost, &base_volume);

    int current_price, current_volume;
    while (1) {
        // Read the current price and volume
        scanf("%d %d", &current_price, &current_volume);

        // Check for the end of input
        if (current_price == -1 && current_volume == -1) {
            break;
        }

        // Read the decrease rate after the maximum known price
        scanf("%d", &decrease_rate);

        // Calculate the profit and tax for each price point
        for (int p = cost; p <= current_price; p++) {
            int volume;
            if (p <= current_price) {
                // Linear interpolation to calculate volume
                volume = base_volume + (current_volume - base_volume) * (p - cost) / (current_price - cost);
            } else {
                // Decrease volume linearly after the maximum known price
                volume = current_volume - (p - current_price) * decrease_rate;
            }

            // Calculate profit and tax
            int profit = (p - cost) * volume;
            int tax = p - price;

            // Update the maximum profit and the corresponding tax
            if (profit > max_profit) {
                max_profit = profit;
                max_profit_tax = tax;
            } else if (profit == max_profit) {
                // Choose the smaller absolute tax value
                if (tax < max_profit_tax) {
                    max_profit_tax = tax;
                }
            }
        }
    }

    // Output the result
    if (max_profit > 0) {
        printf("%d\n", max_profit_tax);
    } else {
        printf("NO SOLUTION\n");
    }

    return 0;
}