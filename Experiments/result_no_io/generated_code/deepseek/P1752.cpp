#include <stdio.h>
#include <stdlib.h>

#define MAX_N 50000
#define MAX_M 200000

typedef struct {
    int deliciousness;
    int price;
} Dish;

int compare_deliciousness(const void *a, const void *b) {
    return ((Dish *)a)->deliciousness - ((Dish *)b)->deliciousness;
}

int compare_price(const void *a, const void *b) {
    return ((Dish *)a)->price - ((Dish *)b)->price;
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
    qsort(dishes, m, sizeof(Dish), compare_deliciousness);
    qsort(dishes, m, sizeof(Dish), compare_price);

    // Sort picky and poor limits
    qsort(picky_limits, p, sizeof(int), compare_deliciousness);
    qsort(poor_limits, q, sizeof(int), compare_price);

    int weeks = 0;
    int picky_index = 0;
    int poor_index = 0;
    int dish_index = 0;

    while (dish_index < m) {
        int picky_count = 0;
        int poor_count = 0;

        // Count how many picky people can eat the current dish
        while (picky_index < p && picky_limits[picky_index] <= dishes[dish_index].deliciousness) {
            picky_count++;
            picky_index++;
        }

        // Count how many poor people can afford the current dish
        while (poor_index < q && poor_limits[poor_index] >= dishes[dish_index].price) {
            poor_count++;
            poor_index++;
        }

        // If no one can eat the current dish, it's impossible to finish all dishes
        if (picky_count == 0 && poor_count == 0) {
            printf("-1\n");
            return 0;
        }

        // Move to the next dish
        dish_index++;
        weeks++;
    }

    printf("%d\n", weeks);
    return 0;
}