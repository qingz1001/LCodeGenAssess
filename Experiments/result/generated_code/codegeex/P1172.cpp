#include <stdio.h>
#include <stdbool.h>

#define MAX_ROWS 50
#define MAX_COLS 50
#define MAX_COWS 100

int rows, cols, numCows;
int cows[MAX_COWS][2];

bool isSafe(int indexToRemove) {
    bool grid[MAX_ROWS][MAX_COLS] = {0};

    for (int i = 0; i < numCows; i++) {
        if (i == indexToRemove) continue;
        grid[cows[i][0]][cows[i][1]] = true;
    }

    for (int i = 0; i < numCows; i++) {
        if (i == indexToRemove) continue;
        int x = cows[i][0], y = cows[i][1];
        bool northFree = true, eastFree = true;

        // Check north
        for (int nx = x - 1; nx >= 0; nx--) {
            if (grid[nx][y]) {
                northFree = false;
                break;
            }
        }

        // Check east
        for (int ny = y + 1; ny < cols; ny++) {
            if (grid[x][ny]) {
                eastFree = false;
                break;
            }
        }

        if (northFree || eastFree) return true;
    }

    return false;
}

int main() {
    scanf("%d %d", &rows, &cols);
    scanf("%d", &numCows);

    for (int i = 0; i < numCows; i++) {
        scanf("%d %d", &cows[i][0], &cows[i][1]);
    }

    bool allSafe = true;
    bool anySafeToRemove = false;
    int safeCows[MAX_COWS] = {0};
    int numSafeCows = 0;

    for (int i = 0; i < numCows; i++) {
        if (!isSafe(i)) {
            allSafe = false;
            safeCows[numSafeCows++] = i + 1;
        } else {
            anySafeToRemove = true;
        }
    }

    if (allSafe) {
        printf("0\n");
    } else if (anySafeToRemove) {
        for (int i = 0; i < numSafeCows; i++) {
            printf("%d\n", safeCows[i]);
        }
    } else {
        printf("-1\n");
    }

    return 0;
}