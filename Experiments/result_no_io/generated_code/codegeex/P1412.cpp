#include <stdio.h>

int main() {
    int n, k, c, w;
    scanf("%d%d%d%d", &n, &k, &c, &w);
    double p = w;
    double max_income = 0;

    for (int i = 0; i < n; i++) {
        int type, x;
        scanf("%d%d", &type, &x);

        if (type == 1) {
            // 资源型星球
            double income = p * x;
            p *= (1 - 0.01 * k);
            max_income += income;
        } else if (type == 2) {
            // 维修型星球
            if (p * (1 + 0.01 * c) > p) {
                // 如果维修后钻头能力值增加，则选择维修
                p *= (1 + 0.01 * c);
            }
        }
    }

    printf("%.2f\n", max_income);
    return 0;
}