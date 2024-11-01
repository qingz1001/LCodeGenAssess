#include <stdio.h>
#include <stdlib.h>

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

    Stone stones[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &stones[i].volume, &stones[i].energy);
    }

    // Sort stones by energy in ascending order
    qsort(stones, n, sizeof(Stone), compare);

    int remaining_volume = v;
    int remaining_energy = c;

    for (int i = 0; i < n; i++) {
        if (stones[i].volume <= remaining_volume && stones[i].energy <= remaining_energy) {
            remaining_volume -= stones[i].volume;
            remaining_energy -= stones[i].energy;
        } else {
            break;
        }
    }

    if (remaining_volume <= 0) {
        printf("%d\n", remaining_energy);
    } else {
        printf("Impossible\n");
    }

    return 0;
}