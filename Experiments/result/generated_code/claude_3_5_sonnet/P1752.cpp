#include <stdio.h>
#include <stdlib.h>

#define MAX_N 50000
#define MAX_M 200000

typedef struct {
    int taste;
    int price;
    int can_order;
} Dish;

int compare_dishes(const void *a, const void *b) {
    return ((Dish *)a)->can_order - ((Dish *)b)->can_order;
}

int main() {
    int n, m, p, q;
    scanf("%d %d %d %d", &n, &m, &p, &q);

    Dish dishes[MAX_M];
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &dishes[i].taste, &dishes[i].price);
        dishes[i].can_order = n;
    }

    int taste_limit[MAX_N], price_limit[MAX_N];
    for (int i = 0; i < p; i++) {
        scanf("%d", &taste_limit[i]);
    }
    for (int i = 0; i < q; i++) {
        scanf("%d", &price_limit[i]);
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            if (dishes[i].taste < taste_limit[j]) {
                dishes[i].can_order--;
            }
        }
        for (int j = 0; j < q; j++) {
            if (dishes[i].price > price_limit[j]) {
                dishes[i].can_order--;
            }
        }
    }

    qsort(dishes, m, sizeof(Dish), compare_dishes);

    int weeks = 0;
    int ordered = 0;
    while (ordered < m && dishes[ordered].can_order > 0) {
        weeks++;
        ordered += n;
        if (ordered > m) ordered = m;
    }

    if (ordered < m) {
        printf("-1\n");
    } else {
        printf("%d\n", weeks);
    }

    return 0;
}