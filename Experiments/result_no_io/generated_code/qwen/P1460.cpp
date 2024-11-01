#include <stdio.h>
#include <stdlib.h>

#define MAX_VITAMINS 26
#define MAX_FEEDS 16

int vitamins[MAX_VITAMINS];
int feed[MAX_FEEDS][MAX_VITAMINS];
int minFeeds[MAX_FEEDS];
int selectedFeeds[MAX_FEEDS];
int numSelected = 0;

void dfs(int index, int currentVitamins[], int currentFeeds[], int count) {
    if (count > numSelected || (count == numSelected && memcmp(selectedFeeds, currentFeeds, sizeof(int) * numSelected) < 0)) {
        memcpy(selectedFeeds, currentFeeds, sizeof(int) * numSelected);
        numSelected = count;
    }
    for (int i = index; i < MAX_FEEDS; i++) {
        int valid = 1;
        for (int j = 0; j < MAX_VITAMINS; j++) {
            if (feed[i][j] + currentVitamins[j] < vitamins[j]) {
                valid = 0;
                break;
            }
        }
        if (valid) {
            for (int j = 0; j < MAX_VITAMINS; j++) {
                currentVitamins[j] += feed[i][j];
            }
            currentFeeds[count] = i + 1;
            dfs(i + 1, currentVitamins, currentFeeds, count + 1);
            for (int j = 0; j < MAX_VITAMINS; j++) {
                currentVitamins[j] -= feed[i][j];
            }
        }
    }
}

int main() {
    int v, g;
    scanf("%d", &v);
    for (int i = 0; i < v; i++) {
        scanf("%d", &vitamins[i]);
    }
    scanf("%d", &g);
    for (int i = 0; i < g; i++) {
        for (int j = 0; j < v; j++) {
            scanf("%d", &feed[i][j]);
        }
    }

    int currentVitamins[MAX_VITAMINS] = {0};
    dfs(0, currentVitamins, selectedFeeds, 0);

    printf("%d ", numSelected);
    for (int i = 0; i < numSelected; i++) {
        printf("%d ", selectedFeeds[i]);
    }
    printf("\n");

    return 0;
}