#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int type; // 0 for normal, 1 for magical
    int value1; // P for normal, P1 for magical
    int value2; // P2 for magical (0 for normal)
} Item;

int compare(const void *a, const void *b) {
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;
    int profitA = itemA->value2 - itemA->value1;
    int profitB = itemB->value2 - itemB->value1;
    return profitB - profitA;
}

int main() {
    int N, Pi;
    scanf("%d %d", &N, &Pi);

    Item items[N];
    int normalCount = 0, magicalCount = 0;

    for (int i = 0; i < N; i++) {
        int P1, P2;
        scanf("%d", &P1);
        if (scanf("%d", &P2) == 1) {
            items[i].type = 1;
            items[i].value1 = P1;
            items[i].value2 = P2;
            magicalCount++;
        } else {
            items[i].type = 0;
            items[i].value1 = P1;
            items[i].value2 = 0;
            normalCount++;
        }
    }

    // Sort magical items by profit (P2 - P1) in descending order
    qsort(items + normalCount, magicalCount, sizeof(Item), compare);

    int money = 0;
    int scrolls = 0;

    for (int i = 0; i < N; i++) {
        if (items[i].type == 0) {
            money += items[i].value1;
        } else {
            if (money >= Pi) {
                money += items[i].value2 - Pi;
            } else {
                money += items[i].value1;
            }
        }
    }

    printf("%d\n", money);

    return 0;
}