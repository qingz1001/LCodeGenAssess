#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);

    int packages[3][2];
    for (int i = 0; i < 3; i++) {
        scanf("%d %d", &packages[i][0], &packages[i][1]);
    }

    int minCost = INT_MAX;
    for (int i = 0; i < 3; i++) {
        int quantity = packages[i][0];
        int price = packages[i][1];
        int numPackages = (n + quantity - 1) / quantity; // 向上取整
        int totalCost = numPackages * price;
        if (totalCost < minCost) {
            minCost = totalCost;
        }
    }

    printf("%d\n", minCost);
    return 0;
}