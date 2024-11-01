#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS 6
#define MAX_TIME 100000
#define MAX_ZOMBIES 2000

int main() {
    int n;
    scanf("%d", &n);

    int zombies[MAX_ZOMBIES][2];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &zombies[i][0], &zombies[i][1]);
    }

    // Sort zombies by their appearance time
    qsort(zombies, n, sizeof(int[2]), compare);

    int nuts[MAX_ROWS] = {0};
    int max_nuts = 0;

    for (int i = 0; i < n; i++) {
        int row = zombies[i][0] - 1;
        int time = zombies[i][1];

        if (time >= 60) continue;

        nuts[row]++;
        if (nuts[row] > max_nuts) {
            max_nuts = nuts[row];
        }
    }

    printf("%d\n", max_nuts);

    return 0;
}

// Comparator function for qsort
int compare(const void *a, const void *b) {
    int *z1 = *(int **)a;
    int *z2 = *(int **)b;
    return z1[1] - z2[1];
}