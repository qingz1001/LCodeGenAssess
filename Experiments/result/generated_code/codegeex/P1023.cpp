#include <stdio.h>

int main() {
    int expected_price, cost, base_price, base_sales, additional_decrease;
    int sales[100001], price[100001], profit[100001];
    int max_profit = -1, best_tax = 0;

    // 读取政府预期价格
    scanf("%d", &expected_price);

    // 读取商品成本和以成本价销售时的销售量
    scanf("%d%d", &cost, &base_sales);
    price[base_price = cost] = sales[cost] = base_sales;

    // 读取各个价位上的销售情况
    while (1) {
        int p, s;
        scanf("%d%d", &p, &s);
        if (p == -1 && s == -1) break;
        price[p] = sales[p] = s;
        if (p < cost) {
            base_price = p;
            base_sales = s;
        }
    }

    // 读取在已知的最高单价外每升高一块钱将减少的销量
    scanf("%d", &additional_decrease);

    // 计算各个价位上的利润
    for (int i = cost; i <= 100000; i++) {
        if (price[i]) {
            sales[i] = price[i];
        } else if (i > expected_price) {
            sales[i] = sales[i - 1] - additional_decrease;
        } else {
            sales[i] = sales[i - 1] + (sales[i - 1] - sales[i - 2]);
        }
        profit[i] = (i - cost) * sales[i];
    }

    // 寻找最大总利润及对应的税金或补贴
    for (int i = base_price; i <= 100000; i++) {
        int tax = i - expected_price;
        if (profit[i] > max_profit) {
            max_profit = profit[i];
            best_tax = tax;
        } else if (profit[i] == max_profit) {
            best_tax = (best_tax > 0) ? best_tax : tax;
        }
    }

    // 输出结果
    if (max_profit > 0) {
        printf("%d\n", best_tax);
    } else {
        printf("NO SOLUTION\n");
    }

    return 0;
}