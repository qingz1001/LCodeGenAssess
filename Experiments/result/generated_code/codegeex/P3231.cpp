#include <stdio.h>
#include <string.h>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        int min_ab = (a < b) ? a : b;
        int min_abc = (min_ab < c) ? min_ab : c;

        int grid[a][b][c];
        memset(grid, 0, sizeof(grid));

        for (int i = 0; i < a; i++) {
            for (int j = 0; j < b; j++) {
                for (int k = 0; k < c; k++) {
                    scanf("%d", &grid[i][j][k]);
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < b; j++) {
                int need_dose = 0;
                for (int k = 0; k < c; k++) {
                    if (grid[i][j][k]) {
                        need_dose = 1;
                        break;
                    }
                }
                if (need_dose) {
                    ans++;
                    for (int k = 0; k < c; k++) {
                        grid[i][j][k] = 0;
                    }
                }
            }
        }

        for (int i = 0; i < a; i++) {
            for (int k = 0; k < c; k++) {
                int need_dose = 0;
                for (int j = 0; j < b; j++) {
                    if (grid[i][j][k]) {
                        need_dose = 1;
                        break;
                    }
                }
                if (need_dose) {
                    ans++;
                    for (int j = 0; j < b; j++) {
                        grid[i][j][k] = 0;
                    }
                }
            }
        }

        for (int j = 0; j < b; j++) {
            for (int k = 0; k < c; k++) {
                int need_dose = 0;
                for (int i = 0; i < a; i++) {
                    if (grid[i][j][k]) {
                        need_dose = 1;
                        break;
                    }
                }
                if (need_dose) {
                    ans++;
                    for (int i = 0; i < a; i++) {
                        grid[i][j][k] = 0;
                    }
                }
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}