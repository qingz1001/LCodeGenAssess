#include <stdio.h>
#include <stdlib.h>

#define MAX_N 50
#define MAX_K 500
#define EPS 1e-6

typedef struct {
    double price;
    int quantity;
} Item;

typedef struct {
    int a, b;
    double discount;
} Discount;

int main() {
    int n, k;
    scanf("%d", &n);
    Item items[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%lf %d", &items[i].price, &items[i].quantity);
    }
    scanf("%d", &k);
    Discount discounts[MAX_K];
    for (int i = 0; i < k; i++) {
        scanf("%d %d %lf", &discounts[i].a, &discounts[i].b, &discounts[i].discount);
    }

    double dp[MAX_N][MAX_N] = {0};
    for (int i = 0; i < n; i++) {
        dp[i][i] = items[i].price * items[i].quantity;
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            dp[i][j] = dp[i][j - 1] + items[j].price * items[j].quantity;
            for (int k = i; k < j; k++) {
                if (dp[i][k] + dp[k + 1][j] - dp[i][j] < dp[i][j]) {
                    dp[i][j] = dp[i][k] + dp[k + 1][j] - dp[i][j];
                }
                for (int l = 0; l < k; l++) {
                    if (discounts[l].a == k + 1 && discounts[l].b == j + 1) {
                        double new_price = dp[i][l] + dp[l + 1][k] + dp[k + 1][j] - dp[i][j];
                        if (new_price < dp[i][j]) {
                            dp[i][j] = new_price;
                        }
                    }
                }
            }
        }
    }

    printf("%.2f\n", dp[0][n - 1]);
    return 0;
}