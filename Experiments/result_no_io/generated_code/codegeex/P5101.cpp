#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXN 1000000
#define MAXM 1000000

int N, M;
int C[MAXN + 1];
int colorCount[MAXM + 1];
int colorIndex[MAXM + 1];
int colorPos[MAXM + 1];
int colorThickness[MAXM + 1];
int minCost[MAXM + 1];

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &C[i]);
    }

    // Initialize color count and index
    memset(colorCount, 0, sizeof(colorCount));
    memset(colorIndex, 0, sizeof(colorIndex));
    memset(colorPos, 0, sizeof(colorPos));
    memset(colorThickness, 0, sizeof(colorThickness));
    memset(minCost, 0, sizeof(minCost));

    // Count the occurrences of each color
    for (int i = 1; i <= N; i++) {
        colorCount[C[i]]++;
    }

    // Calculate the minimum cost for each color
    for (int color = 1; color <= M; color++) {
        if (colorCount[color] == 0) continue;

        int thickness = 0;
        int minThickness = INT_MAX;
        int lastPos = 0;

        for (int i = 1; i <= N; i++) {
            if (C[i] == color) {
                thickness++;
                minThickness = thickness;
                lastPos = i;
            }
        }

        for (int i = 1; i <= N; i++) {
            if (C[i] == color) {
                thickness--;
                minThickness = thickness < minThickness ? thickness : minThickness;
            }
        }

        minCost[color] = minThickness;
    }

    // Output the minimum cost for each color
    for (int color = 1; color <= M; color++) {
        printf("%d\n", minCost[color]);
    }

    return 0;
}