#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_SIZE 5000

int min(int a, int b) {
    return a < b ? a : b;
}

int min3(int a, int b, int c) {
    return min(min(a, b), c);
}

int main() {
    int D;
    scanf("%d", &D);
    while (D--) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        int grid[a][b][c];
        memset(grid, 0, sizeof(grid));

        for (int i = 0; i < a; i++) {
            for (int j = 0; j < b; j++) {
                for (int k = 0; k < c; k++) {
                    scanf("%d", &grid[i][j][k]);
                }
            }
        }

        int min_dim = min3(a, b, c);
        int min_units = INT_MAX;

        for (int x = 1; x <= min_dim; x++) {
            int units = 0;
            for (int i = 0; i < a; i += x) {
                for (int j = 0; j < b; j += x) {
                    for (int k = 0; k < c; k += x) {
                        int count = 0;
                        for (int ii = i; ii < i + x && ii < a; ii++) {
                            for (int jj = j; jj < j + x && jj < b; jj++) {
                                for (int kk = k; kk < k + x && kk < c; kk++) {
                                    if (grid[ii][jj][kk] == 1) {
                                        count++;
                                    }
                                }
                            }
                        }
                        units += (count > 0) ? 1 : 0;
                    }
                }
            }
            min_units = min(min_units, units);
        }

        printf("%d\n", min_units);
    }
    return 0;
}