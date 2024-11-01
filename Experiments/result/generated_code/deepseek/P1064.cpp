#include <stdio.h>
#include <stdlib.h>

#define MAX_M 60
#define MAX_N 32000

typedef struct {
    int price;
    int importance;
    int mainItem;
} Item;

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Item items[MAX_M + 1];
    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d", &items[i].price, &items[i].importance, &items[i].mainItem);
    }

    int dp[MAX_N + 1] = {0};

    for (int i = 1; i <= m; i++) {
        if (items[i].mainItem == 0) {
            for (int j = n; j >= items[i].price; j--) {
                dp[j] = max(dp[j], dp[j - items[i].price] + items[i].price * items[i].importance);

                if (items[i].mainItem == 0) {
                    int mainPrice = items[i].price;
                    int mainImportance = items[i].price * items[i].importance;

                    for (int k = 1; k <= m; k++) {
                        if (items[k].mainItem == i) {
                            int subPrice = items[k].price;
                            int subImportance = items[k].price * items[k].importance;

                            if (j >= mainPrice + subPrice) {
                                dp[j] = max(dp[j], dp[j - mainPrice - subPrice] + mainImportance + subImportance);
                            }

                            for (int l = k + 1; l <= m; l++) {
                                if (items[l].mainItem == i) {
                                    int subPrice2 = items[l].price;
                                    int subImportance2 = items[l].price * items[l].importance;

                                    if (j >= mainPrice + subPrice + subPrice2) {
                                        dp[j] = max(dp[j], dp[j - mainPrice - subPrice - subPrice2] + mainImportance + subImportance + subImportance2);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    printf("%d\n", dp[n]);

    return 0;
}