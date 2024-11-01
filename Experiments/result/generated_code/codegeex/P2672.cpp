#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int s;
    int a;
} House;

int compare(const void *a, const void *b) {
    House *houseA = (House *)a;
    House *houseB = (House *)b;
    if (houseA->s == houseB->s) {
        return houseA->a - houseB->a;
    }
    return houseA->s - houseB->s;
}

int main() {
    int n;
    scanf("%d", &n);
    House houses[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &houses[i].s);
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &houses[i].a);
    }

    qsort(houses, n, sizeof(House), compare);

    long long totalFatigue = 0;
    long long maxFatigue[n + 1];
    maxFatigue[0] = 0;

    for (int x = 1; x <= n; x++) {
        if (x == 1) {
            totalFatigue += houses[0].s * 2 + houses[0].a;
        } else {
            if (houses[x - 1].s != houses[x - 2].s) {
                totalFatigue += houses[x - 1].s * 2;
            }
            totalFatigue += houses[x - 1].a;
        }
        maxFatigue[x] = totalFatigue;
    }

    for (int i = 1; i <= n; i++) {
        printf("%lld\n", maxFatigue[i]);
    }

    return 0;
}