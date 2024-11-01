#include <stdio.h>

int main() {
    int n, k, c, w;
    scanf("%d%d%d%d", &n, &k, &c, &w);
    int type, x;
    double max_profit = 0.0;

    for (int i = 0; i < n; i++) {
        scanf("%d%d", &type, &x);
        if (type == 1) {
            // 资源型星球
            double profit = w * x * (1 - 0.01 * k);
            max_profit += profit;
            w *= (1 - 0.01 * k);
        } else if (type == 2) {
            // 维修型星球
            if (w * x * (1 + 0.01 * c) > w) {
                // 维修后钻头能力值增加
                w *= (1 + 0.01 * c);
            }
        }
    }

    printf("%.2f\n", max_profit);
    return 0;
}