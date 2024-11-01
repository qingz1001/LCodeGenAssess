#include <stdio.h>
#include <stdlib.h>

int clocks[9];
int moves[9][9] = {
    {1, 1, 0, 1, 1, 0, 0, 0, 0},
    {1, 1, 1, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 1, 1, 0, 0, 0},
    {1, 0, 0, 1, 0, 0, 1, 0, 0},
    {0, 1, 0, 1, 1, 1, 0, 1, 0},
    {0, 0, 1, 0, 0, 1, 0, 0, 1},
    {0, 0, 0, 1, 1, 0, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 1, 1, 1},
    {0, 0, 0, 0, 1, 1, 0, 1, 1}
};

int min_moves[9] = {0};
int best_solution[9] = {0};
int min_count = 1000000;

void apply_moves(int *clocks, int move, int count) {
    for (int i = 0; i < 9; i++) {
        if (moves[move][i]) {
            clocks[i] = (clocks[i] + count) % 4;
        }
    }
}

int check_clocks(int *clocks) {
    for (int i = 0; i < 9; i++) {
        if (clocks[i] != 0) {
            return 0;
        }
    }
    return 1;
}

void dfs(int depth, int *current_moves) {
    if (depth == 9) {
        int temp_clocks[9];
        for (int i = 0; i < 9; i++) {
            temp_clocks[i] = clocks[i];
        }
        for (int i = 0; i < 9; i++) {
            apply_moves(temp_clocks, i, current_moves[i]);
        }
        if (check_clocks(temp_clocks)) {
            int total_count = 0;
            for (int i = 0; i < 9; i++) {
                total_count += current_moves[i];
            }
            if (total_count < min_count) {
                min_count = total_count;
                for (int i = 0; i < 9; i++) {
                    best_solution[i] = current_moves[i];
                }
            }
        }
        return;
    }
    for (int i = 0; i < 4; i++) {
        current_moves[depth] = i;
        dfs(depth + 1, current_moves);
    }
}

int main() {
    for (int i = 0; i < 9; i++) {
        scanf("%d", &clocks[i]);
        clocks[i] = (clocks[i] / 3) % 4;
    }

    int current_moves[9] = {0};
    dfs(0, current_moves);

    int first = 1;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < best_solution[i]; j++) {
            if (!first) {
                printf(" ");
            }
            printf("%d", i + 1);
            first = 0;
        }
    }
    printf("\n");

    return 0;
}