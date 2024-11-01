#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

typedef struct {
    int p1;
    int p2;
    int diff;
} Item;

int compare(const void *a, const void *b) {
    return ((Item *)b)->diff - ((Item *)a)->diff;
}

int main() {
    int N, Pi;
    scanf("%d %d", &N, &Pi);

    Item items[MAX_N];
    int normal_sum = 0;
    int magic_count = 0;

    for (int i = 0; i < N; i++) {
        int p1, p2;
        scanf("%d", &p1);
        if (scanf("%d", &p2) == 1) {
            items[magic_count].p1 = p1;
            items[magic_count].p2 = p2;
            items[magic_count].diff = p2 - p1 - Pi;
            magic_count++;
        } else {
            normal_sum += p1;
        }
    }

    qsort(items, magic_count, sizeof(Item), compare);

    long long total = normal_sum;
    long long current = normal_sum;

    for (int i = 0; i < magic_count; i++) {
        if (current >= Pi) {
            if (items[i].diff > 0) {
                current -= Pi;
                current += items[i].p2;
                total += items[i].p2;
            } else {
                current += items[i].p1;
                total += items[i].p1;
            }
        } else {
            current += items[i].p1;
            total += items[i].p1;
        }
    }

    printf("%lld\n", total);

    return 0;
}