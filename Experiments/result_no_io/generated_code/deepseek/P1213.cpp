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

int best_solution[9] = {0};
int best_count = 1000000;

void apply_moves(int *clocks, int move, int count) {
    for (int i = 0; i < 9; i++) {
        if (moves[move][i]) {
            clocks[i] = (clocks[i] + count) % 4;
        }
    }
}

int is_solved(int *clocks) {
    for (int i = 0; i < 9; i++) {
        if (clocks[i] != 0) return 0;
    }
    return 1;
}

void solve(int depth, int *solution) {
    if (depth == 9) {
        int temp_clocks[9];
        for (int i = 0; i < 9; i++) {
            temp_clocks[i] = clocks[i];
        }
        for (int i = 0; i < 9; i++) {
            apply_moves(temp_clocks, i, solution[i]);
        }
        if (is_solved(temp_clocks)) {
            int total_count = 0;
            for (int i = 0; i < 9; i++) {
                total_count += solution[i];
            }
            if (total_count < best_count) {
                best_count = total_count;
                for (int i = 0; i < 9; i++) {
                    best_solution[i] = solution[i];
                }
            }
        }
        return;
    }
    for (int i = 0; i < 4; i++) {
        solution[depth] = i;
        solve(depth + 1, solution);
    }
}

int main() {
    for (int i = 0; i < 9; i++) {
        scanf("%d", &clocks[i]);
        clocks[i] = (clocks[i] / 3) % 4;
    }

    int solution[9] = {0};
    solve(0, solution);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < best_solution[i]; j++) {
            printf("%d ", i + 1);
        }
    }
    printf("\n");

    return 0;
}