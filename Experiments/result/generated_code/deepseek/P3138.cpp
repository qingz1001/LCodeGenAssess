#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000
#define MAX_COORD 1000000

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
    int x_coords[MAXN];
    for (int i = 0; i < N; i++) {
        x_coords[i] = cows[i].x;
    }

    qsort(cows, N, sizeof(Cow), compareY);
    int y_coords[MAXN];
    for (int i = 0; i < N; i++) {
        y_coords[i] = cows[i].y;
    }

    int min_M = N;

    // Try all possible even x and y coordinates for the fences
    for (int i = 0; i < N; i++) {
        int a = x_coords[i] + 1; // a is even
        if (a % 2 != 0) continue;
        for (int j = 0; j < N; j++) {
            int b = y_coords[j] + 1; // b is even
            if (b % 2 != 0) continue;

            int count[4] = {0};
            for (int k = 0; k < N; k++) {
                if (cows[k].x < a && cows[k].y < b) count[0]++;
                else if (cows[k].x < a && cows[k].y > b) count[1]++;
                else if (cows[k].x > a && cows[k].y < b) count[2]++;
                else if (cows[k].x > a && cows[k].y > b) count[3]++;
            }

            int max_count = 0;
            for (int k = 0; k < 4; k++) {
                if (count[k] > max_count) max_count = count[k];
            }

            if (max_count < min_M) min_M = max_count;
        }
    }

    printf("%d\n", min_M);
    return 0;
}