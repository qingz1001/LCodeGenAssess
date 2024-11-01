#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int deliciousness;
    int price;
} Dish;

int compare(const void *a, const void *b) {
    Dish *dishA = (Dish*)a;
    Dish *dishB = (Dish*)b;
    if (dishA->deliciousness != dishB->deliciousness) {
        return dishA->deliciousness - dishB->deliciousness;
    } else {
        return dishA->price - dishB->price;
    }
}

int main() {
    int n, m, p, q;
    scanf("%d %d %d %d", &n, &m, &p, &q);

    Dish dishes[m];
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &dishes[i].deliciousness, &dishes[i].price);
    }

    int minDeliciousness[p];
    for (int i = 0; i < p; i++) {
        scanf("%d", &minDeliciousness[i]);
    }

    int maxPrice[q];
    for (int i = 0; i < q; i++) {
        scanf("%d", &maxPrice[i]);
    }

    qsort(dishes, m, sizeof(Dish), compare);

    int minWeeks = -1;
    int currentWeek = 1;
    int currentIndex = 0;

    while (currentIndex < m) {
        Dish currentDish = dishes[currentIndex];
        int eligibleCount = 0;

        for (int i = 0; i < p; i++) {
            if (currentDish.deliciousness >= minDeliciousness[i]) {
                eligibleCount++;
            }
        }

        for (int i = 0; i < q; i++) {
            if (currentDish.price <= maxPrice[i]) {
                eligibleCount++;
            }
        }

        if (eligibleCount >= n) {
            currentIndex++;
        } else {
            currentWeek++;
            if (currentWeek > m) {
                minWeeks = -1;
                break;
            }
        }
    }

    if (minWeeks == -1) {
        printf("-1\n");
    } else {
        printf("%d\n", currentWeek);
    }

    return 0;
}