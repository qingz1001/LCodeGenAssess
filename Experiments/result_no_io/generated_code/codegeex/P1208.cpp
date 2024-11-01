#include <stdio.h>

// 定义一个结构体来存储每个农民的信息
typedef struct {
    int price;  // 牛奶单价
    int amount; // 牛奶量
} Farmer;

// 比较函数，用于qsort排序
int compare(const void *a, const void *b) {
    Farmer *farmerA = (Farmer *)a;
    Farmer *farmerB = (Farmer *)b;
    return farmerA->price - farmerB->price;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Farmer farmers[5000];

    // 读取每个农民的单价和牛奶量
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &farmers[i].price, &farmers[i].amount);
    }

    // 按照单价从小到大排序
    qsort(farmers, m, sizeof(Farmer), compare);

    int totalMilk = 0; // 已经购买的牛奶总量
    int totalCost = 0; // 总花费

    // 贪心算法，优先购买单价最低的牛奶
    for (int i = 0; i < m; i++) {
        if (totalMilk < n) {
            int milkToBuy = farmers[i].amount;
            if (totalMilk + milkToBuy > n) {
                milkToBuy = n - totalMilk;
            }
            totalCost += milkToBuy * farmers[i].price;
            totalMilk += milkToBuy;
        }
    }

    printf("%d\n", totalCost);
    return 0;
}