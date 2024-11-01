#include <stdio.h>

int main() {
    int n, a, b, c, d, e, f, min_cost;
    
    // 输入需要的铅笔数量
    scanf("%d", &n);
    
    // 输入三种包装的铅笔数量和价格
    scanf("%d %d", &a, &b);
    scanf("%d %d", &c, &d);
    scanf("%d %d", &e, &f);
    
    // 计算购买三种包装铅笔所需的最小花费
    int cost1 = (n + a - 1) / a * b; // 向上取整
    int cost2 = (n + c - 1) / c * d; // 向上取整
    int cost3 = (n + e - 1) / e * f; // 向上取整
    
    // 找出最小的花费
    min_cost = cost1;
    if (cost2 < min_cost) {
        min_cost = cost2;
    }
    if (cost3 < min_cost) {
        min_cost = cost3;
    }
    
    // 输出最小花费
    printf("%d\n", min_cost);
    
    return 0;
}