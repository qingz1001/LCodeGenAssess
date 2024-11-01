#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000

typedef struct {
    int volume;
    int energy;
} Stone;

int compare(const void *a, const void *b) {
    Stone *stoneA = (Stone *)a;
    Stone *stoneB = (Stone *)b;
    return stoneA->energy - stoneB->energy;
}

int main() {
    int v, n, c;
    scanf("%d %d %d", &v, &n, &c);

    Stone stones[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &stones[i].volume, &stones[i].energy);
    }

    qsort(stones, n, sizeof(Stone), compare);

    int total_volume = 0;
    int remaining_energy = c;

    for (int i = 0; i < n; i++) {
        if (remaining_energy >= stones[i].energy) {
            total_volume += stones[i].volume;
            remaining_energy -= stones[i].energy;

            if (total_volume >= v) {
                printf("%d\n", remaining_energy);
                return 0;
            }
        } else {
            break;
        }
    }

    printf("Impossible\n");
    return 0;
}