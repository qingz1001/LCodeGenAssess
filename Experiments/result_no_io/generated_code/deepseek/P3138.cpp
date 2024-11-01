#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000
#define MAXCOORD 1000000

typedef struct {
    int x, y;
} Cow;

int compareX(const void *a, const void *b) {
    return ((Cow *)a)->x - ((Cow *)b)->x;
}

int compareY(const void *a, const void *b) {
    return ((Cow *)a)->y - ((Cow *)b)->y;
}

int main() {
    int N;
    Cow cows[MAXN];
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &cows[i].x, &cows[i].y);
    }

    // Sort cows by x and y coordinates
    qsort(cows, N, sizeof(Cow), compareX);
    int xCoords[MAXN];
    for (int i = 0; i < N; i++) {
        xCoords[i] = cows[i].x;
    }

    qsort(cows, N, sizeof(Cow), compareY);
    int yCoords[MAXN];
    for (int i = 0; i < N; i++) {
        yCoords[i] = cows[i].y;
    }

    int minM = N;

    // Try all possible even x and y coordinates for the fences
    for (int i = 0; i < N; i++) {
        if (xCoords[i] % 2 != 0) continue;
        for (int j = 0; j < N; j++) {
            if (yCoords[j] % 2 != 0) continue;

            int count[4] = {0};
            for (int k = 0; k < N; k++) {
                if (cows[k].x < xCoords[i] && cows[k].y < yCoords[j]) {
                    count[0]++;
                } else if (cows[k].x < xCoords[i] && cows[k].y > yCoords[j]) {
                    count[1]++;
                } else if (cows[k].x > xCoords[i] && cows[k].y < yCoords[j]) {
                    count[2]++;
                } else if (cows[k].x > xCoords[i] && cows[k].y > yCoords[j]) {
                    count[3]++;
                }
            }

            int maxCount = 0;
            for (int k = 0; k < 4; k++) {
                if (count[k] > maxCount) {
                    maxCount = count[k];
                }
            }

            if (maxCount < minM) {
                minM = maxCount;
            }
        }
    }

    printf("%d\n", minM);
    return 0;
}