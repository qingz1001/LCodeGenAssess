#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define INF 1e9

typedef struct {
    long long a, s, c, x;
} Vegetable;

int compare(const void *a, const void *b) {
    return ((Vegetable *)b)->a - ((Vegetable *)a)->a;
}

long long calculateProfit(Vegetable *veggies, int n, int m, int p) {
    qsort(veggies, n, sizeof(Vegetable), compare);
    long long profit = 0;
    for (int i = 0; i < n && m > 0; i++) {
        int sell = m > veggies[i].c ? veggies[i].c : m;
        profit += sell * veggies[i].a + (sell == veggies[i].c ? veggies[i].s : 0);
        m -= sell;
    }
    return profit;
}

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    Vegetable veggies[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld %lld %lld", &veggies[i].a, &veggies[i].s, &veggies[i].c, &veggies[i].x);
    }
    while (k--) {
        int p;
        scanf("%d", &p);
        printf("%lld\n", calculateProfit(veggies, n, m, p));
    }
    return 0;
}