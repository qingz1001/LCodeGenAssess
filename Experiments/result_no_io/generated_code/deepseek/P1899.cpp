#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int type; // 0 for normal, 1 for magical
    int P1;   // Value before identification
    int P2;   // Value after identification
} Item;

int compare(const void *a, const void *b) {
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;
    int gainA = itemA->P2 - itemA->P1;
    int gainB = itemB->P2 - itemB->P1;
    return gainB - gainA;
}

int main() {
    int N, Pi;
    scanf("%d %d", &N, &Pi);

    Item items[N];
    int normalCount = 0;
    int magicalCount = 0;

    for (int i = 0; i < N; i++) {
        int P1, P2;
        scanf("%d", &P1);
        if (scanf("%d", &P2) == 1) {
            items[i].type = 1;
            items[i].P1 = P1;
            items[i].P2 = P2;
            magicalCount++;
        } else {
            items[i].type = 0;
            items[i].P1 = P1;
            items[i].P2 = P1;
            normalCount++;
        }
    }

    // Sort magical items by the gain from identification
    qsort(items + normalCount, magicalCount, sizeof(Item), compare);

    int money = 0;
    int scrolls = 0;

    for (int i = 0; i < N; i++) {
        if (items[i].type == 0) {
            money += items[i].P1;
        } else {
            if (money >= Pi) {
                money += items[i].P2 - Pi;
                scrolls++;
            } else {
                money += items[i].P1;
            }
        }
    }

    printf("%d\n", money);

    return 0;
}