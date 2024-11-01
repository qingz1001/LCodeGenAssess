#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int distance;
    int fatigue;
} House;

int compare(const void *a, const void *b) {
    House *houseA = (House *)a;
    House *houseB = (House *)b;
    return houseB->fatigue - houseA->fatigue;
}

int main() {
    int N;
    scanf("%d", &N);

    House *houses = (House *)malloc(N * sizeof(House));
    for (int i = 0; i < N; i++) {
        scanf("%d", &houses[i].distance);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &houses[i].fatigue);
    }

    // Sort houses by fatigue in descending order
    qsort(houses, N, sizeof(House), compare);

    int maxDistance = 0;
    for (int i = 0; i < N; i++) {
        if (houses[i].distance > maxDistance) {
            maxDistance = houses[i].distance;
        }
    }

    int *totalFatigue = (int *)malloc(N * sizeof(int));
    int currentFatigue = 0;
    for (int i = 0; i < N; i++) {
        currentFatigue += houses[i].fatigue;
        totalFatigue[i] = currentFatigue + 2 * maxDistance;
    }

    for (int i = 0; i < N; i++) {
        printf("%d\n", totalFatigue[i]);
    }

    free(houses);
    free(totalFatigue);

    return 0;
}