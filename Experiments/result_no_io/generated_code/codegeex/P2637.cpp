#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int *prices = (int *)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        scanf("%d", &prices[i]);
    }
    
    // 对价格进行排序
    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < m - i - 1; j++) {
            if (prices[j] > prices[j + 1]) {
                int temp = prices[j];
                prices[j] = prices[j + 1];
                prices[j + 1] = temp;
            }
        }
    }
    
    int maxProfit = 0;
    int bestPrice = 0;
    for (int i = 0; i < m; i++) {
        int currentProfit = (i + 1) * prices[i];
        if (currentProfit > maxProfit) {
            maxProfit = currentProfit;
            bestPrice = prices[i];
        }
    }
    
    printf("%d %d\n", bestPrice, maxProfit);
    free(prices);
    
    return 0;
}