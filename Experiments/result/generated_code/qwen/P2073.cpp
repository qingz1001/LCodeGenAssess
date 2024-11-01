#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int beauty;
    int cost;
} Flower;

int compareByCost(const void *a, const void *b) {
    return ((Flower *)b)->cost - ((Flower *)a)->cost;
}

int compareByBeauty(const void *a, const void *b) {
    return ((Flower *)a)->beauty - ((Flower *)b)->beauty;
}

int main() {
    int m;
    scanf("%d", &m);
    Flower flowers[m];
    int index = 0;
    while (m != -1) {
        if (m == 1) {
            int w, c;
            scanf("%d %d", &w, &c);
            flowers[index].beauty = w;
            flowers[index].cost = c;
            for (int i = 0; i < index; i++) {
                if (flowers[i].cost == c) {
                    goto next;
                }
            }
            index++;
        } else if (m == 2 && index > 0) {
            qsort(flowers, index, sizeof(Flower), compareByCost);
            index--;
        } else if (m == 3 && index > 0) {
            qsort(flowers, index, sizeof(Flower), compareByBeauty);
            index--;
        }
next:
        scanf("%d", &m);
    }

    int totalBeauty = 0, totalPrice = 0;
    for (int i = 0; i < index; i++) {
        totalBeauty += flowers[i].beauty;
        totalPrice += flowers[i].cost;
    }

    printf("%d %d\n", totalBeauty, totalPrice);

    return 0;
}