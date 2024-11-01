#include <stdio.h>
#include <stdlib.h>

#define MAX_M 200000
#define MAX_N 50000

typedef struct {
    int deliciousness;
    int price;
} Dish;

int compare_dishes(const void *a, const void *b) {
    Dish *dishA = (Dish *)a;
    Dish *dishB = (Dish *)b;
    if (dishA->deliciousness != dishB->deliciousness) {
        return dishA->deliciousness - dishB->deliciousness;
    } else {
        return dishA->price - dishB->price;
    }
}

int main() {
    int n, m, p, q;
    scanf("%d %d %d %d", &n, &m, &p, &q);

    Dish dishes[MAX_M];
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &dishes[i].deliciousness, &dishes[i].price);
    }

    int picky_limits[MAX_N];
    for (int i = 0; i < p; i++) {
        scanf("%d", &picky_limits[i]);
    }

    int poor_limits[MAX_N];
    for (int i = 0; i < q; i++) {
        scanf("%d", &poor_limits[i]);
    }

    // Sort dishes by deliciousness and price
    qsort(dishes, m, sizeof(Dish), compare_dishes);

    // Sort picky and poor limits
    qsort(picky_limits, p, sizeof(int), compare_dishes);
    qsort(poor_limits, q, sizeof(int), compare_dishes);

    int weeks = 0;
    int dish_index = 0;
    int picky_index = 0;
    int poor_index = 0;

    while (dish_index < m) {
        int picky_count = 0;
        int poor_count = 0;

        while (picky_index < p && picky_limits[picky_index] <= dishes[dish_index].deliciousness) {
            picky_index++;
            picky_count++;
        }

        while (poor_index < q && poor_limits[poor_index] >= dishes[dish_index].price) {
            poor_index++;
            poor_count++;
        }

        if (picky_count + poor_count > 0) {
            weeks++;
            dish_index++;
        } else {
            break;
        }
    }

    if (dish_index == m) {
        printf("%d\n", weeks);
    } else {
        printf("-1\n");
    }

    return 0;
}