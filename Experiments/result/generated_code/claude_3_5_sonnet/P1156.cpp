#include <stdio.h>
#include <stdlib.h>

#define MAX_GARBAGE 100
#define MAX_TIME 1001

typedef struct {
    int time;
    int food;
    int height;
} Garbage;

int compare(const void *a, const void *b) {
    return ((Garbage*)a)->time - ((Garbage*)b)->time;
}

int main() {
    int D, G;
    scanf("%d %d", &D, &G);

    Garbage garbage[MAX_GARBAGE];
    for (int i = 0; i < G; i++) {
        scanf("%d %d %d", &garbage[i].time, &garbage[i].food, &garbage[i].height);
    }

    qsort(garbage, G, sizeof(Garbage), compare);

    int dp[MAX_TIME] = {0};
    int maxHeight = 0;
    int maxTime = 10;
    int escapeTime = -1;

    for (int i = 0; i < G; i++) {
        int t = garbage[i].time;
        int f = garbage[i].food;
        int h = garbage[i].height;

        // Update maxTime
        if (t <= maxTime) {
            maxTime = (maxTime > t + f) ? maxTime : t + f;
        }

        // Update dp array
        for (int j = maxTime; j >= t; j--) {
            if (j - t <= 10 || dp[j - t] > 0) {
                dp[j] = (dp[j] > dp[j - t] + h) ? dp[j] : dp[j - t] + h;
                if (dp[j] >= D && escapeTime == -1) {
                    escapeTime = j;
                }
            }
        }

        // Update maxHeight
        maxHeight = (maxHeight > dp[t]) ? maxHeight : dp[t];

        if (escapeTime != -1) break;
    }

    if (escapeTime != -1) {
        printf("%d\n", escapeTime);
    } else {
        printf("%d\n", maxTime);
    }

    return 0;
}