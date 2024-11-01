#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXK 100005

typedef struct {
    long long a, s, c, x;
} Vegetable;

Vegetable vegetables[MAXN];
long long max_days[MAXK];
long long max_profit[MAXK];

int compare(const void *a, const void *b) {
    Vegetable *v1 = (Vegetable *)a;
    Vegetable *v2 = (Vegetable *)b;
    return (v2->a + v2->s) - (v1->a + v1->s);
}

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    for (int i = 0; i < n; i++) {
        scanf("%lld %lld %lld %lld", &vegetables[i].a, &vegetables[i].s, &vegetables[i].c, &vegetables[i].x);
    }

    for (int i = 0; i < k; i++) {
        scanf("%lld", &max_days[i]);
    }

    qsort(vegetables, n, sizeof(Vegetable), compare);

    for (int i = 0; i < k; i++) {
        long long days = max_days[i];
        long long profit = 0;
        long long remaining_capacity = m * days;

        for (int j = 0; j < n && remaining_capacity > 0; j++) {
            long long a = vegetables[j].a;
            long long s = vegetables[j].s;
            long long c = vegetables[j].c;
            long long x = vegetables[j].x;

            long long max_units = (x == 0) ? c : (c / x + (c % x != 0));
            long long units_to_sell = (max_units < remaining_capacity) ? max_units : remaining_capacity;

            if (units_to_sell > 0) {
                profit += units_to_sell * a;
                if (units_to_sell == max_units) {
                    profit += s;
                }
                remaining_capacity -= units_to_sell;
            }
        }

        max_profit[i] = profit;
    }

    for (int i = 0; i < k; i++) {
        printf("%lld\n", max_profit[i]);
    }

    return 0;
}