#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long a, s, c, x;
} Vegetable;

long long maxProfit(Vegetable *vegetables, int n, int m, int p) {
    long long totalProfit = 0;
    for (int i = 0; i < n; i++) {
        if (vegetables[i].x == 0) {
            long long days = (vegetables[i].c + vegetables[i].x - 1) / vegetables[i].x;
            long long sellDays = days <= p ? days : p;
            long long sellUnits = sellDays * m;
            long long unitsToSell = sellUnits > vegetables[i].c ? vegetables[i].c : sellUnits;
            totalProfit += (unitsToSell * vegetables[i].a) + (sellDays * vegetables[i].s);
        } else {
            long long remainingUnits = vegetables[i].c;
            for (int day = 1; day <= p && remainingUnits > 0; day++) {
                long long sellUnits = day * m > remainingUnits ? remainingUnits : day * m;
                totalProfit += (sellUnits * vegetables[i].a) + (day * vegetables[i].s);
                remainingUnits -= sellUnits;
            }
        }
    }
    return totalProfit;
}

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    Vegetable *vegetables = (Vegetable *)malloc(n * sizeof(Vegetable));
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld %lld %lld", &vegetables[i].a, &vegetables[i].s, &vegetables[i].c, &vegetables[i].x);
    }
    for (int j = 0; j < k; j++) {
        int p;
        scanf("%d", &p);
        printf("%lld\n", maxProfit(vegetables, n, m, p));
    }
    free(vegetables);
    return 0;
}