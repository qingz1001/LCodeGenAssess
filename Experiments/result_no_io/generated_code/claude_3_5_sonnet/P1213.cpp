#include <stdio.h>
#include <string.h>

#define MAX_MOVES 20

int clocks[9];
int moves[9][5] = {
    {0, 1, 3, 4, -1},
    {0, 1, 2, -1},
    {1, 2, 4, 5, -1},
    {0, 3, 6, -1},
    {1, 3, 4, 5, 7},
    {2, 5, 8, -1},
    {3, 4, 6, 7, -1},
    {6, 7, 8, -1},
    {4, 5, 7, 8, -1}
};

int solution[MAX_MOVES];
int min_solution[MAX_MOVES];
int min_len = MAX_MOVES;

void rotate(int move) {
    for (int i = 0; moves[move][i] != -1; i++) {
        clocks[moves[move][i]] = (clocks[moves[move][i]] + 3) % 12;
    }
}

int is_solved() {
    for (int i = 0; i < 9; i++) {
        if (clocks[i] != 0) return 0;
    }
    return 1;
}

void solve(int depth, int last_move) {
    if (depth >= min_len) return;
    
    if (is_solved()) {
        if (depth < min_len) {
            min_len = depth;
            memcpy(min_solution, solution, depth * sizeof(int));
        }
        return;
    }
    
    for (int i = last_move; i < 9; i++) {
        for (int j = 1; j <= 3; j++) {
            rotate(i);
            solution[depth] = i;
            solve(depth + 1, i);
        }
        rotate(i);
    }
}

int main() {
    for (int i = 0; i < 9; i++) {
        scanf("%d", &clocks[i]);
        clocks[i] = (clocks[i] / 3) % 4;
    }
    
    solve(0, 0);
    
    for (int i = 0; i < min_len; i++) {
        printf("%d ", min_solution[i] + 1);
    }
    printf("\n");
    
    return 0;
}