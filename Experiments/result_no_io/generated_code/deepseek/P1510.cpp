#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int volume;
    int effort;
} Stone;

int compare(const void *a, const void *b) {
    Stone *stoneA = (Stone *)a;
    Stone *stoneB = (Stone *)b;
    return stoneA->effort - stoneB->effort;
}

int main() {
    int v, n, c;
    scanf("%d %d %d", &v, &n, &c);

    Stone stones[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &stones[i].volume, &stones[i].effort);
    }

    // Sort stones by effort in ascending order
    qsort(stones, n, sizeof(Stone), compare);

    int totalVolume = 0;
    int remainingEffort = c;

    for (int i = 0; i < n; i++) {
        if (totalVolume >= v) {
            break;
        }
        if (stones[i].effort <= remainingEffort) {
            totalVolume += stones[i].volume;
            remainingEffort -= stones[i].effort;
        }
    }

    if (totalVolume >= v) {
        printf("%d\n", remainingEffort);
    } else {
        printf("Impossible\n");
    }

    return 0;
}