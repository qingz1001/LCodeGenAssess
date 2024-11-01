#include <stdio.h>
#include <stdlib.h>

int n, k, h;
int colorCount[100];
int totalLayouts = 0;

void backtrack(int row, int col, int usedRows[], int usedCols[], int count[]) {
    if (row == n) {
        if (count[0] == k) {
            totalLayouts++;
        }
        return;
    }

    if (col == n) {
        backtrack(row + 1, 0, usedRows, usedCols, count);
        return;
    }

    for (int c = 0; c < h; c++) {
        if (count[c] < colorCount[c]) {
            if (!usedRows[row] && !usedCols[col]) {
                usedRows[row] = 1;
                usedCols[col] = 1;
                count[c]++;
                backtrack(row, col + 1, usedRows, usedCols, count);
                count[c]--;
                usedCols[col] = 0;
                usedRows[row] = 0;
            }
            usedRows[row] = 1;
            backtrack(row, col + 1, usedRows, usedCols, count);
            usedRows[row] = 0;
            usedCols[col] = 1;
            backtrack(row, col + 1, usedRows, usedCols, count);
            usedCols[col] = 0;
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &k, &h);
    int total = 0;
    for (int i = 0; i < h; i++) {
        scanf("%d", &colorCount[i]);
        total += colorCount[i];
    }

    if (total != k) {
        printf("0\n");
        return 0;
    }

    int *usedRows = (int *)calloc(n, sizeof(int));
    int *usedCols = (int *)calloc(n, sizeof(int));
    int *count = (int *)calloc(h, sizeof(int));

    backtrack(0, 0, usedRows, usedCols, count);

    printf("%d\n", totalLayouts);

    free(usedRows);
    free(usedCols);
    free(count);

    return 0;
}