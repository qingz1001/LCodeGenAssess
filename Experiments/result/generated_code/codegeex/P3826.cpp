#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef long long ll;

struct Vegetable {
    ll profit_per_unit;
    ll initial_profit;
    ll total_units;
    ll spoilage_rate;
};

ll compare(const void *a, const void *b) {
    const Vegetable *v1 = (const Vegetable *)a;
    const Vegetable *v2 = (const Vegetable *)b;
    return v1->profit_per_unit - v2->profit_per_unit;
}

ll max_profit(Vegetable *vegetables, int n, int m, int p) {
    ll total_profit = 0;
    ll remaining_days = p;
    ll remaining_units = m;

    qsort(vegetables, n, sizeof(Vegetable), compare);

    for (int i = 0; i < n && remaining_units > 0; i++) {
        Vegetable *v = &vegetables[i];
        ll units_to_sell = 0;

        if (v->spoilage_rate > 0) {
            ll days_until_spoilage = (v->total_units + v->spoilage_rate - 1) / v->spoilage_rate;
            if (days_until_spoilage <= remaining_days) {
                units_to_sell = v->total_units;
            } else {
                units_to_sell = v->spoilage_rate * remaining_days;
            }
        } else {
            units_to_sell = v->total_units;
        }

        if (units_to_sell > remaining_units) {
            units_to_sell = remaining_units;
        }

        ll profit_from_units = units_to_sell * v->profit_per_unit;
        ll profit_from_initial = (i == 0) ? v->initial_profit : 0;

        total_profit += profit_from_units + profit_from_initial;
        remaining_units -= units_to_sell;
        remaining_days -= (units_to_sell / v->spoilage_rate);
    }

    return total_profit;
}

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    Vegetable *vegetables = (Vegetable *)malloc(n * sizeof(Vegetable));
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld %lld %lld", &vegetables[i].profit_per_unit, &vegetables[i].initial_profit, &vegetables[i].total_units, &vegetables[i].spoilage_rate);
    }

    for (int i = 0; i < k; i++) {
        int p;
        scanf("%d", &p);
        printf("%lld\n", max_profit(vegetables, n, m, p));
    }

    free(vegetables);
    return 0;
}