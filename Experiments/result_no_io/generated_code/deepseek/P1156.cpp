#include <stdio.h>
#include <stdlib.h>

#define MAX_D 100
#define MAX_G 100
#define INITIAL_ENERGY 10

typedef struct {
    int time;
    int life;
    int height;
} Trash;

int compare(const void *a, const void *b) {
    return ((Trash *)a)->time - ((Trash *)b)->time;
}

int main() {
    int D, G;
    scanf("%d %d", &D, &G);

    Trash trash[MAX_G];
    for (int i = 0; i < G; i++) {
        scanf("%d %d %d", &trash[i].time, &trash[i].life, &trash[i].height);
    }

    qsort(trash, G, sizeof(Trash), compare);

    int dp[MAX_D + 1];
    for (int i = 0; i <= D; i++) {
        dp[i] = -1;
    }
    dp[0] = INITIAL_ENERGY;

    for (int i = 0; i < G; i++) {
        for (int j = D; j >= 0; j--) {
            if (dp[j] >= trash[i].time) {
                if (j + trash[i].height >= D) {
                    printf("%d\n", trash[i].time);
                    return 0;
                }
                if (dp[j + trash[i].height] < dp[j]) {
                    dp[j + trash[i].height] = dp[j];
                }
                if (dp[j] + trash[i].life > dp[j]) {
                    dp[j] += trash[i].life;
                }
            }
        }
    }

    int max_life = INITIAL_ENERGY;
    for (int i = 0; i < G; i++) {
        if (max_life >= trash[i].time) {
            max_life += trash[i].life;
        }
    }

    printf("%d\n", max_life);
    return 0;
}