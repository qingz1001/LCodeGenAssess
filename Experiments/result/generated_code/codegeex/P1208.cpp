#include <stdio.h>
#include <stdlib.h>

// 定义一个结构体来存储每个农民的牛奶单价和产量
typedef struct {
    int price;
    int amount;
} Farmer;

// 比较函数，用于qsort排序
int compare(const void *a, const void *b) {
    Farmer *farmerA = (Farmer *)a;
    Farmer *farmerB = (Farmer *)b;
    return farmerA->price - farmerB->price;
}

int main() {
    int n, m;
    // 读取需要的牛奶总量和农民数量
    scanf("%d %d", &n, &m);

    Farmer farmers[5000];

    // 读取每个农民的单价和产量
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &farmers[i].price, &farmers[i].amount);
    }

    // 按照单价从小到大排序
    qsort(farmers, m, sizeof(Farmer), compare);

    int totalMilk = 0;
    int totalCost = 0;

    // 依次购买牛奶，直到满足需求
    for (int i = 0; i < m; i++) {
        if (totalMilk >= n) {
            break;
        }
        int milkToBuy = farmers[i].amount;
        if (totalMilk + milkToBuy > n) {
            milkToBuy = n - totalMilk;
        }
        totalMilk += milkToBuy;
        totalCost += milkToBuy * farmers[i].price;
    }

    // 输出最小花费
    printf("%d\n", totalCost);

    return 0;
}