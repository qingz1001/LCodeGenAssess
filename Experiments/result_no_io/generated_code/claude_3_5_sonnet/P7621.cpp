#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int total = 0;
    for (int i = 0; i < n; i++) {
        int price, quantity;
        scanf("%d.%d %d", &price, &quantity, &quantity);
        total += price * 100 + quantity;
        total *= quantity;
    }

    total = (total * 85 + 5000) / 10000;
    printf("%.1f\n", total / 10.0);

    return 0;
}