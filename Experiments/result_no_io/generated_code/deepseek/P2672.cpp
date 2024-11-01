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

    qsort(houses, N, sizeof(House), compare);

    int *maxFatigue = (int *)malloc(N * sizeof(int));
    int maxDistance = 0;
    int totalFatigue = 0;

    for (int i = 0; i < N; i++) {
        totalFatigue += houses[i].fatigue;
        if (houses[i].distance > maxDistance) {
            maxDistance = houses[i].distance;
        }
        maxFatigue[i] = totalFatigue + 2 * maxDistance;
    }

    for (int i = 0; i < N; i++) {
        printf("%d\n", maxFatigue[i]);
    }

    free(houses);
    free(maxFatigue);

    return 0;
}