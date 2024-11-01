#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int s;
    int a;
} House;

int cmp(const void *a, const void *b) {
    House *houseA = (House *)a;
    House *houseB = (House *)b;
    return houseA->a - houseB->a;
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

    qsort(houses, n, sizeof(House), cmp);

    int totalFatigue = 0;
    int maxFatigue[n];
    maxFatigue[0] = houses[0].a + houses[0].s * 2;

    for (int i = 1; i < n; i++) {
        totalFatigue += houses[i-1].a;
        maxFatigue[i] = totalFatigue + houses[i].s * 2 + houses[i].a;
    }

    for (int i = 0; i < n; i++) {
        printf("%d\n", maxFatigue[i]);
    }

    return 0;
}