#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int prices[1001];
    for (int i = 0; i < m; i++) {
        scanf("%d", &prices[i]);
    }
    
    // 对价格进行排序
    for (int i = 0; i < m - 1; i++) {
        for (int j = i + 1; j < m; j++) {
            if (prices[i] > prices[j]) {
                int temp = prices[i];
                prices[i] = prices[j];
                prices[j] = temp;
            }
        }
    }
    
    int maxProfit = 0;
    int bestPrice = 0;
    
    // 找出能卖出最多钱的最低价格
    for (int i = 0; i <= m - n; i++) {
        int currentProfit = (n * prices[i]);
        if (currentProfit > maxProfit) {
            maxProfit = currentProfit;
            bestPrice = prices[i];
        }
    }
    
    printf("%d %d\n", bestPrice, maxProfit);
    
    return 0;
}