#include <stdio.h>
#include <stdlib.h>

#define MAX_R 500
#define MAX_C 500
#define MAX_N 4000

int R, C, A, B;
int brownie[MAX_R][MAX_C];
int min_chips = INT_MAX;

void dfs(int row, int col, int remaining_cows, int current_chips) {
    if (remaining_cows == 0) {
        min_chips = (min_chips > current_chips) ? current_chips : min_chips;
        return;
    }
    if (row >= R || col >= C) return;

    int max_chips_in_strip = 0;
    for (int i = row; i < row + A; i++) {
        for (int j = col; j < col + B; j++) {
            max_chips_in_strip += brownie[i][j];
        }
    }

    for (int i = row; i < row + A; i++) {
        for (int j = col; j < col + B; j++) {
            int new_chips = current_chips + brownie[i][j];
            dfs(i + 1, col, remaining_cows - 1, new_chips);
        }
    }
}

int main() {
    scanf("%d %d %d %d", &R, &C, &A, &B);

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            scanf("%d", &brownie[i][j]);
        }
    }

    dfs(0, 0, A * B - 1, 0);

    printf("%d\n", min_chips);

    return 0;
}