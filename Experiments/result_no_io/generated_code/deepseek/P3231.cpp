#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE 5000

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int a, b, c;
bool grid[MAX_SIZE][MAX_SIZE];

int min_f_units(int x, int y, int z) {
    int min_units = INT_MAX;
    for (int i = 1; i <= x; i++) {
        for (int j = 1; j <= y; j++) {
            for (int k = 1; k <= z; k++) {
                if (grid[i][j]) {
                    min_units = min(min_units, min(i, min(j, k)));
                }
            }
        }
    }
    return min_units;
}

int main() {
    int D;
    scanf("%d", &D);
    while (D--) {
        scanf("%d %d %d", &a, &b, &c);
        for (int i = 1; i <= a; i++) {
            for (int j = 1; j <= b; j++) {
                for (int k = 1; k <= c; k++) {
                    int val;
                    scanf("%d", &val);
                    grid[j][k] = val;
                }
            }
        }
        printf("%d\n", min_f_units(a, b, c));
    }
    return 0;
}