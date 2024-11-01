#include <stdio.h>

// 定义金币堆的结构体
typedef struct {
    double weight; // 重量
    double value;  // 价值
} Coin;

// 比较函数，用于qsort排序
int compare(const void *a, const void *b) {
    Coin *coinA = (Coin *)a;
    Coin *coinB = (Coin *)b;
    // 按照价值/重量的比值降序排列
    return (coinB->value / coinB->weight - coinA->value / coinA->weight) * 1000000;
}

int main() {
    int N;
    double T;
    // 读取金币堆的数量和背包的承重量
    scanf("%d %lf", &N, &T);

    Coin coins[N];
    // 读取每堆金币的重量和价值
    for (int i = 0; i < N; i++) {
        scanf("%lf %lf", &coins[i].weight, &coins[i].value);
    }

    // 按照价值/重量的比值降序排列
    qsort(coins, N, sizeof(Coin), compare);

    double totalValue = 0.0; // 背包中金币的总价值
    double remainingWeight = T; // 背包剩余的承重量

    // 遍历每堆金币
    for (int i = 0; i < N; i++) {
        if (remainingWeight >= coins[i].weight) {
            // 如果当前金币堆的重量小于背包剩余承重量，则全部装入
            totalValue += coins[i].value;
            remainingWeight -= coins[i].weight;
        } else {
            // 如果当前金币堆的重量大于背包剩余承重量，则只装入部分
            totalValue += coins[i].value / coins[i].weight * remainingWeight;
            break; // 背包已满，退出循环
        }
    }

    // 输出背包中金币的总价值，保留两位小数
    printf("%.2lf\n", totalValue);

    return 0;
}