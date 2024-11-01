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
        for (int i = 1; i <= a; ++i) {
            for (int j = 1; j <= b; ++j) {
                for (int k = 1; k <= c; ++k) {
                    scanf("%d", &grid[i][j][k]);
                }
            }
        }

        long long min_chemistry = 0;

        for (int i = 1; i <= a; ++i) {
            for (int j = 1; j <= b; ++j) {
                for (int k = 1; k <= c; ++k) {
                    if (grid[i][j][k]) {
                        int x = i, y = j, z = k;
                        while (x <= a && grid[x][y][z]) {
                            while (y <= b && grid[x][y][z]) {
                                while (z <= c && grid[x][y][z]) {
                                    ++z;
                                }
                                --z;
                                min_chemistry += (long long)min(min(x, y), z);
                                x++;
                            }
                            --y;
                            z = k;
                        }
                        --x;
                        y = j;
                    }
                }
            }
        }

        printf("%lld\n", min_chemistry);
    }
    return 0;
}