#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

typedef struct {
    int p1;
    int p2;
    int is_magic;
} Item;

int compare(const void *a, const void *b) {
    Item *item_a = (Item *)a;
    Item *item_b = (Item *)b;
    return (item_b->p2 - item_b->p1) - (item_a->p2 - item_a->p1);
}

int main() {
    int N, Pi;
    scanf("%d %d", &N, &Pi);

    Item items[MAX_N];
    int total_value = 0;

    for (int i = 0; i < N; i++) {
        int p1, p2;
        if (scanf("%d %d", &p1, &p2) == 2) {
            items[i].p1 = p1;
            items[i].p2 = p2;
            items[i].is_magic = 1;
        } else {
            items[i].p1 = p1;
            items[i].p2 = p1;
            items[i].is_magic = 0;
        }
        total_value += items[i].p1;
    }

    qsort(items, N, sizeof(Item), compare);

    for (int i = 0; i < N; i++) {
        if (items[i].is_magic && total_value >= Pi) {
            total_value = total_value - Pi + items[i].p2 - items[i].p1;
        }
    }

    printf("%d\n", total_value);

    return 0;
}