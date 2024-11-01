#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXK 100005

typedef struct {
    long long a, s, c, x;
} Vegetable;

Vegetable vegetables[MAXN];
long long p[MAXK];
long long max_days[MAXK];
long long max_profit[MAXK];

int compare(const void *a, const void *b) {
    return *(long long *)b - *(long long *)a;
}

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    for (int i = 0; i < n; i++) {
        scanf("%lld %lld %lld %lld", &vegetables[i].a, &vegetables[i].s, &vegetables[i].c, &vegetables[i].x);
    }

    for (int i = 0; i < k; i++) {
        scanf("%lld", &p[i]);
    }

    for (int i = 0; i < k; i++) {
        long long days = p[i];
        long long total_profit = 0;

        for (int j = 0; j < n; j++) {
            long long a = vegetables[j].a;
            long long s = vegetables[j].s;
            long long c = vegetables[j].c;
            long long x = vegetables[j].x;

            long long available = c;
            if (x > 0) {
                long long full_days = c / x;
                if (full_days >= days) {
                    available = days * x;
                } else {
                    available = c - full_days * x;
                }
            }

            long long sell_count = available;
            if (sell_count > m * days) {
                sell_count = m * days;
            }

            total_profit += sell_count * a;
            if (sell_count > 0) {
                total_profit += s;
            }
        }

        max_profit[i] = total_profit;
    }

    for (int i = 0; i < k; i++) {
        printf("%lld\n", max_profit[i]);
    }

    return 0;
}