#include <stdio.h>
#include <string.h>

#define MAXN 10

int main() {
    int n;
    char grid[MAXN][MAXN][4];
    char letters[MAXN * MAXN];
    int values[MAXN * MAXN];
    int num_letters = 0;

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%s", grid[i][j]);
            if (grid[i][j][0] != '+' && strchr(letters, grid[i][j][0]) == NULL) {
                letters[num_letters++] = grid[i][j][0];
            }
        }
    }

    for (int i = 0; i < num_letters; i++) {
        for (int j = 0; j <= 9; j++) {
            values[i] = j;
            int valid = 1;
            for (int k = 0; k < n; k++) {
                for (int l = 0; l < n; l++) {
                    if (grid[k][l][0] != '+' && grid[k][l][0] != '\0') {
                        int sum = 0;
                        for (int m = 0; m < n - 1; m++) {
                            if (grid[k][m][0] != '+')
                                sum += values[strchr(letters, grid[k][m][0]) - letters];
                        }
                        if (values[strchr(letters, grid[k][l][0]) - letters] != sum % 10) {
                            valid = 0;
                            break;
                        }
                    }
                }
                if (!valid)
                    break;
            }
            if (valid) {
                printf("%c=%d ", letters[i], values[i]);
            } else {
                printf("ERROR!\n");
                return 0;
            }
        }
    }

    int base = 0;
    for (int i = 0; i < n; i++) {
        if (strlen(grid[0][i]) > 1) {
            base = strlen(grid[0][i]);
            break;
        }
    }
    printf("\n%d\n", base);

    return 0;
}