#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);

    int min_cost = 1000000000; // 初始化一个很大的值

    for (int i = 0; i < 3; i++) {
        int quantity, price;
        scanf("%d %d", &quantity, &price);

        int packages_needed = (n + quantity - 1) / quantity; // 向上取整
        int total_cost = packages_needed * price;

        if (total_cost < min_cost) {
            min_cost = total_cost;
        }
    }

    printf("%d\n", min_cost);

    return 0;
}