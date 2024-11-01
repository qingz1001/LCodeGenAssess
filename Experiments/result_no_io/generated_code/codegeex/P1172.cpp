#include <stdio.h>
#include <stdbool.h>

#define MAX_ROW 50
#define MAX_COL 50
#define MAX_COW 100

int main() {
    int r, c, n;
    scanf("%d%d%d", &r, &c, &n);

    int cows[MAX_COW][2];
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &cows[i][0], &cows[i][1]);
    }

    bool unsafe = false;
    int unsafe_cows[MAX_COW];

    // Check each cow for potential conflicts
    for (int i = 0; i < n; i++) {
        bool north_clear = true;
        bool east_clear = true;

        for (int j = 0; j < n; j++) {
            if (i == j) continue;

            if (cows[j][0] == cows[i][0] - 1 && cows[j][1] == cows[i][1]) {
                north_clear = false;
            }
            if (cows[j][0] == cows[i][0] && cows[j][1] == cows[i][1] + 1) {
                east_clear = false;
            }
        }

        if (north_clear || east_clear) {
            unsafe = true;
            unsafe_cows[i] = 1;
        } else {
            unsafe_cows[i] = 0;
        }
    }

    // Determine the output based on the safety analysis
    bool one_safe = false;
    bool all_unsafe = true;

    for (int i = 0; i < n; i++) {
        if (unsafe_cows[i]) {
            all_unsafe = false;
            if (one_safe) {
                printf("%d\n", i + 1);
            } else {
                one_safe = true;
            }
        }
    }

    if (all_unsafe) {
        printf("-1\n");
    } else if (one_safe) {
        printf("0\n");
    }

    return 0;
}