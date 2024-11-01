#include <stdio.h>
#include <stdbool.h>

#define MAX_N 500
#define MAX_COORD 10000

int C, N;
int clovers[MAX_N][2];

bool containsAtLeastC(int sideLength) {
    int xCount[MAX_COORD + 1] = {0};
    int yCount[MAX_COORD + 1] = {0};

    for (int i = 0; i < N; i++) {
        int x = clovers[i][0];
        int y = clovers[i][1];
        xCount[x]++;
        yCount[y]++;
    }

    for (int x = 1; x <= MAX_COORD - sideLength + 1; x++) {
        for (int y = 1; y <= MAX_COORD - sideLength + 1; y++) {
            int count = 0;
            for (int i = 0; i < sideLength; i++) {
                for (int j = 0; j < sideLength; j++) {
                    count += xCount[x + i] && yCount[y + j];
                }
            }
            if (count >= C) return true;
        }
    }
    return false;
}

int main() {
    scanf("%d %d", &C, &N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &clovers[i][0], &clovers[i][1]);
    }

    int left = 1, right = MAX_COORD;
    while (left < right) {
        int mid = (left + right) / 2;
        if (containsAtLeastC(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    printf("%d\n", left);
    return 0;
}