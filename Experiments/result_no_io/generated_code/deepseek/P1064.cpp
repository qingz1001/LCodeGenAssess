#include <stdio.h>
#include <stdlib.h>

#define MAX_N 32000
#define MAX_M 60

typedef struct {
    int price;
    int importance;
    int main_item;
} Item;

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Item items[MAX_M + 1];
    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d", &items[i].price, &items[i].importance, &items[i].main_item);
    }

    int dp[MAX_N + 1] = {0};

    for (int i = 1; i <= m; i++) {
        if (items[i].main_item == 0) {
            for (int j = n; j >= items[i].price; j--) {
                dp[j] = max(dp[j], dp[j - items[i].price] + items[i].price * items[i].importance);
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        if (items[i].main_item != 0) {
            int main_item = items[i].main_item;
            for (int j = n; j >= items[main_item].price + items[i].price; j--) {
                dp[j] = max(dp[j], dp[j - items[main_item].price - items[i].price] + items[main_item].price * items[main_item].importance + items[i].price * items[i].importance);
            }
        }
    }

    printf("%d\n", dp[n]);

    return 0;
}