#include <stdio.h>

typedef struct {
    double m; // 重量
    double v; // 价值
} Coin;

int main() {
    int n, T;
    scanf("%d %d", &n, &T);
    
    Coin coins[100];
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &coins[i].m, &coins[i].v);
    }
    
    // 按照单位价值从大到小排序
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (coins[i].v / coins[i].m < coins[j].v / coins[j].m) {
                Coin temp = coins[i];
                coins[i] = coins[j];
                coins[j] = temp;
            }
        }
    }
    
    double totalValue = 0.0;
    double remainingWeight = T;
    
    for (int i = 0; i < n; i++) {
        if (remainingWeight >= coins[i].m) {
            totalValue += coins[i].v;
            remainingWeight -= coins[i].m;
        } else {
            totalValue += coins[i].v / coins[i].m * remainingWeight;
            break;
        }
    }
    
    printf("%.2lf\n", totalValue);
    return 0;
}