#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef struct {
    int t, g, m;
} Order;

int cmp(const void *a, const void *b) {
    return ((Order *)a)->t - ((Order *)b)->t;
}

int main() {
    int n;
    scanf("%d", &n);
    Order orders[MAXN];
    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d", &orders[i].t, &orders[i].g, &orders[i].m);
    }
    qsort(orders, n, sizeof(Order), cmp);

    int time = 0, money = 0, products = 0, productivity = 1;
    int i = 0;
    while (time < 100000 || i < n) {
        if (i < n && orders[i].t == time) {
            int need_products = orders[i].g;
            while (products < need_products) {
                if (productivity + 1 <= 100000) {
                    productivity++;
                    time++;
                } else {
                    products += productivity;
                    time++;
                }
            }
            money += orders[i].m;
            i++;
        } else {
            if (productivity + 1 <= 100000) {
                productivity++;
                time++;
            } else {
                products += productivity;
                time++;
            }
        }
    }

    printf("%d\n", money);
    return 0;
}