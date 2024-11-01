#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    while (1) {
        scanf("%d", &n);
        if (n == 0) break;

        int *sides = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            scanf("%d", &sides[i]);
        }

        int *visible = (int *)calloc(n, sizeof(int));
        int max_side = 0;
        int max_index = -1;

        for (int i = 0; i < n; i++) {
            if (sides[i] > max_side) {
                max_side = sides[i];
                max_index = i;
            }
        }

        visible[max_index] = 1;

        for (int i = max_index + 1; i < n; i++) {
            if (sides[i] > sides[i - 1]) {
                visible[i] = 1;
            }
        }

        for (int i = max_index - 1; i >= 0; i--) {
            if (sides[i] > sides[i + 1]) {
                visible[i] = 1;
            }
        }

        for (int i = 0; i < n; i++) {
            if (visible[i]) {
                printf("%d ", i + 1);
            }
        }
        printf("\n");

        free(sides);
        free(visible);
    }
    return 0;
}