#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int p1;
    int p2;
} MagicItem;

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int compareMagic(const void *a, const void *b) {
    return ((MagicItem*)a)->p2 - ((MagicItem*)b)->p2;
}

int main() {
    int N, P_i;
    scanf("%d %d", &N, &P_i);

    int* normalItems = (int*)malloc(N * sizeof(int));
    MagicItem* magicItems = (MagicItem*)malloc(N * sizeof(MagicItem));
    int normalCount = 0;
    int magicCount = 0;

    for (int i = 0; i < N; i++) {
        int p1, p2;
        scanf("%d", &p1);
        if (scanf("%d", &p2) != EOF) {
            magicItems[magicCount].p1 = p1;
            magicItems[magicCount].p2 = p2;
            magicCount++;
        } else {
            normalItems[normalCount++] = p1;
        }
    }

    qsort(normalItems, normalCount, sizeof(int), compare);
    qsort(magicItems, magicCount, sizeof(MagicItem), compareMagic);

    int money = 0;
    int remainingPotions = N;

    for (int i = 0; i < normalCount; i++) {
        money += normalItems[i];
        remainingPotions--;
    }

    for (int i = 0; i < magicCount; i++) {
        if (remainingPotions * P_i >= magicItems[i].p1) {
            money += magicItems[i].p2;
            remainingPotions--;
        } else {
            money += magicItems[i].p1;
        }
    }

    printf("%d\n", money);

    free(normalItems);
    free(magicItems);

    return 0;
}