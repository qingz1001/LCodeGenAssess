#include <stdio.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int main() {
    int n, x, y;
    scanf("%d %d %d", &n, &x, &y);

    int total_cost = 0;
    for (int i = 0; i < n; i++) {
        int ai;
        scanf("%d", &ai);
        
        // 比较单程票总价和单日票价格，选择较小的
        total_cost += MIN(ai * x, y);
    }

    printf("%d\n", total_cost);

    return 0;
}