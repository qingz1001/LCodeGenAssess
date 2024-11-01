#include <stdio.h>
#include <stdlib.h>

#define MAXN 5005

int main() {
    int D;
    scanf("%d", &D);
    while (D--) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        int grid[MAXN][MAXN][MAXN];
        for (int i = 0; i < a; ++i) {
            for (int j = 0; j < b; ++j) {
                for (int k = 0; k < c; ++k) {
                    scanf("%d", &grid[i][j][k]);
                }
            }
        }

        int min_chemistry = 0;
        for (int i = 0; i < a; ++i) {
            for (int j = 0; j < b; ++j) {
                for (int k = 0; k < c; ++k) {
                    if (grid[i][j][k]) {
                        int x = 1, y = 1, z = 1;
                        while (i + x < a && grid[i + x][j][k]) ++x;
                        while (j + y < b && grid[i][j + y][k]) ++y;
                        while (k + z < c && grid[i][j][k + z]) ++z;
                        min_chemistry += x * y * z;
                        for (int ii = i; ii < i + x; ++ii) {
                            for (int jj = j; jj < j + y; ++jj) {
                                for (int kk = k; kk < k + z; ++kk) {
                                    grid[ii][jj][kk] = 0;
                                }
                            }
                        }
                        --i;
                        --j;
                        --k;
                    }
                }
            }
        }
        printf("%d\n", min_chemistry);
    }
    return 0;
}