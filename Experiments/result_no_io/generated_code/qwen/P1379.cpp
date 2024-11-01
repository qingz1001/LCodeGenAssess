#include <stdio.h>
#include <stdlib.h>

#define SIZE 9

int goal[SIZE] = {1, 2, 3, 8, 0, 4, 7, 6, 5};
int initial[SIZE];
int visited[SIZE * SIZE];

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int isGoal(int state[]) {
    for (int i = 0; i < SIZE; i++) {
        if (state[i] != goal[i]) return 0;
    }
    return 1;
}

int getZeroIndex(int state[]) {
    for (int i = 0; i < SIZE; i++) {
        if (state[i] == 0) return i;
    }
    return -1;
}

int heuristic(int state[]) {
    int h = 0;
    for (int i = 0; i < SIZE; i++) {
        if (state[i] != goal[i] && state[i] != 0) {
            int goalIndex = -1;
            for (int j = 0; j < SIZE; j++) {
                if (goal[j] == state[i]) {
                    goalIndex = j;
                    break;
                }
            }
            int rowDiff = abs(i / 3 - goalIndex / 3);
            int colDiff = abs(i % 3 - goalIndex % 3);
            h += rowDiff + colDiff;
        }
    }
    return h;
}

void printState(int state[]) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", state[i]);
        if ((i + 1) % 3 == 0) printf("\n");
    }
}

void aStar() {
    int openList[SIZE * SIZE][SIZE], closedList[SIZE * SIZE][SIZE];
    int openCount = 0, closedCount = 0;

    // Initialize open list with the initial state
    memcpy(openList[openCount++], initial, sizeof(initial));

    while (openCount > 0) {
        int minF = INT_MAX, minIndex = -1;
        for (int i = 0; i < openCount; i++) {
            int f = heuristic(openList[i]);
            if (f < minF) {
                minF = f;
                minIndex = i;
            }
        }

        memcpy(closedList[closedCount++], openList[minIndex], sizeof(initial));
        openCount--;

        if (isGoal(closedList[closedCount - 1])) {
            printf("0\n");
            return;
        }

        int zeroIndex = getZeroIndex(closedList[closedCount - 1]);

        int neighbors[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (int i = 0; i < 4; i++) {
            int newZeroIndex = zeroIndex + neighbors[i][0] * 3 + neighbors[i][1];
            if (newZeroIndex >= 0 && newZeroIndex < SIZE && (newZeroIndex / 3 == zeroIndex / 3 || newZeroIndex % 3 == zeroIndex % 3)) {
                int newState[SIZE];
                memcpy(newState, closedList[closedCount - 1], sizeof(initial));
                swap(&newState[zeroIndex], &newState[newZeroIndex]);
                if (!visited[newState[0] * 9 + newState[1] * 3 + newState[2]]) {
                    visited[newState[0] * 9 + newState[1] * 3 + newState[2]] = 1;
                    memcpy(openList[openCount++], newState, sizeof(initial));
                }
            }
        }
    }
}

int main() {
    for (int i = 0; i < SIZE; i++) {
        scanf("%d", &initial[i]);
    }

    aStar();

    return 0;
}