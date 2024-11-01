#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    double total = 0.0;

    for (int i = 0; i < n; i++) {
        double price;
        int quantity;
        scanf("%lf %d", &price, &quantity);
        total += price * quantity;
    }

    // Apply 85% discount
    total *= 0.85;

    // Calculate the number of cents
    int cents = total * 100;

    // Calculate the number of full yuan and remaining cents
    int yuan = cents / 100;
    cents %= 100;

    // Print the result with one decimal place
    printf("%d.%02d\n", yuan, cents);

    return 0;
}