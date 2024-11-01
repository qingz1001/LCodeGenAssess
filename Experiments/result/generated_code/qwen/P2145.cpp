#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500

int n;
int colors[MAX_N];

void removeConsecutive(int *colors, int *length) {
    int i = 0;
    while (i < *length) {
        int j = i + 1;
        while (j < *length && colors[j] == colors[i]) {
            j++;
        }
        if (j - i >= 3) {
            memmove(colors + i, colors + j, (*length - j) * sizeof(int));
            *length -= j - i;
            i = 0;
        } else {
            i = j;
        }
    }
}

int minShots() {
    int minShots = n;
    for (int color = 1; color <= 32; color++) {
        int tempColors[MAX_N];
        memcpy(tempColors, colors, n * sizeof(int));
        int length = n;
        int shots = 0;

        while (length > 0) {
            int found = 0;
            for (int i = 0; i < length; i++) {
                if (tempColors[i] != color) {
                    continue;
                }
                int j = i + 1;
                while (j < length && tempColors[j] == color) {
                    j++;
                }
                if (j - i >= 3) {
                    memmove(tempColors + i, tempColors + j, (length - j) * sizeof(int));
                    length -= j - i;
                    shots++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                break;
            }
        }

        if (shots < minShots) {
            minShots = shots;
        }
    }
    return minShots;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &colors[i]);
    }

    printf("%d\n", minShots());

    return 0;
}