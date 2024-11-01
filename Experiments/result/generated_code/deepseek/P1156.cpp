#include <stdio.h>
#include <stdlib.h>

#define MAX_D 100
#define MAX_G 100
#define INITIAL_ENERGY 10

typedef struct {
    int time;
    int life;
    int height;
} Garbage;

int compare(const void *a, const void *b) {
    return ((Garbage *)a)->time - ((Garbage *)b)->time;
}

int main() {
    int D, G;
    scanf("%d %d", &D, &G);

    Garbage garbages[MAX_G];
    for (int i = 0; i < G; i++) {
        scanf("%d %d %d", &garbages[i].time, &garbages[i].life, &garbages[i].height);
    }

    qsort(garbages, G, sizeof(Garbage), compare);

    int dp[MAX_D + 1];
    for (int i = 0; i <= D; i++) {
        dp[i] = -1;
    }
    dp[0] = INITIAL_ENERGY;

    for (int i = 0; i < G; i++) {
        for (int j = D; j >= 0; j--) {
            if (dp[j] >= garbages[i].time) {
                if (j + garbages[i].height >= D) {
                    printf("%d\n", garbages[i].time);
                    return 0;
                }
                if (dp[j + garbages[i].height] < dp[j]) {
                    dp[j + garbages[i].height] = dp[j];
                }
                if (dp[j] + garbages[i].life > dp[j]) {
                    dp[j] += garbages[i].life;
                }
            }
        }
    }

    int max_life = INITIAL_ENERGY;
    for (int i = 0; i < G; i++) {
        if (dp[0] >= garbages[i].time) {
            max_life += garbages[i].life;
        }
    }

    printf("%d\n", max_life);
    return 0;
}