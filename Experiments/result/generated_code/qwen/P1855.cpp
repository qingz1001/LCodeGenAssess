#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_M 200
#define MAX_T 200

typedef struct {
    int money;
    int time;
} Wish;

int compare(const void *a, const void *b) {
    Wish *wishA = (Wish *)a;
    Wish *wishB = (Wish *)b;
    if (wishA->money != wishB->money) return wishA->money - wishB->money;
    return wishA->time - wishB->time;
}

int main() {
    int n, M, T;
    scanf("%d %d %d", &n, &M, &T);

    Wish wishes[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &wishes[i].money, &wishes[i].time);
    }

    qsort(wishes, n, sizeof(Wish), compare);

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (wishes[i].money <= M && wishes[i].time <= T) {
            M -= wishes[i].money;
            T -= wishes[i].time;
            count++;
        }
    }

    printf("%d\n", count);
    return 0;
}