#include <stdio.h>

int a[5][5] = {0};

void print_solution() {
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void solve(int row, int col) {
    if (row == 4 && col == 5) {
        print_solution();
        return;
    }

    if (col == 5) {
        row++;
        col = 1;
    }

    for (int num = 2; num <= 16; num++) {
        if (a[row][col] == 0) {
            a[row][col] = num;

            // Check if the current number placement is valid
            if ((a[1][1] + a[1][4] + a[4][1] + a[4][4] == 34) &&
                (a[1][1] + a[1][2] + a[2][1] + a[2][2] == 34) &&
                (a[2][2] + a[2][3] + a[3][2] + a[3][3] == 34) &&
                (a[1][1] + a[2][1] + a[3][1] + a[4][1] == 34) &&
                (a[1][2] + a[2][2] + a[3][2] + a[4][2] == 34) &&
                (a[1][3] + a[2][3] + a[3][3] + a[4][3] == 34) &&
                (a[1][4] + a[2][4] + a[3][4] + a[4][4] == 34) &&
                (a[1][1] + a[2][2] + a[3][3] + a[4][4] == 34) &&
                (a[1][4] + a[2][3] + a[3][2] + a[4][1] == 34)) {
                
                solve(row, col + 1);
            }

            a[row][col] = 0;
        }
    }
}

int main() {
    int i, j;
    scanf("%d %d", &i, &j);
    a[i][j] = 1;
    solve(1, 1);
    return 0;
}