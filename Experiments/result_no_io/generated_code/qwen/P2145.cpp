#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500

int n;
int beads[MAX_N];

int min(int a, int b) {
    return a < b ? a : b;
}

void removeConsecutive(int *beads, int *length) {
    int i = 0, j = 0;
    while (j < *length) {
        if (j == 0 || beads[j] != beads[j - 1]) {
            beads[i++] = beads[j];
        }
        j++;
    }
    *length = i;
}

int shootBeads(int color) {
    int result = 0;
    int length = n;
    int temp[MAX_N];
    for (int i = 0; i < length; i++) {
        temp[i] = beads[i];
    }

    while (1) {
        int removed = 0;
        for (int i = 0; i < length; i++) {
            if (temp[i] == color && (i + 2 < length && temp[i] == temp[i + 1] && temp[i] == temp[i + 2])) {
                int start = i;
                while (i + 1 < length && temp[i] == temp[i + 1]) {
                    i++;
                }
                for (int j = start; j <= i; j++) {
                    temp[j] = 0;
                }
                removed = 1;
            }
        }
        if (!removed) break;
        removeConsecutive(temp, &length);
    }

    for (int i = 0; i < length; i++) {
        if (temp[i] != 0) {
            result++;
        }
    }

    return result;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &beads[i]);
    }

    int minShots = n;
    for (int i = 0; i < n; i++) {
        minShots = min(minShots, shootBeads(beads[i]));
    }

    printf("%d\n", minShots);

    return 0;
}