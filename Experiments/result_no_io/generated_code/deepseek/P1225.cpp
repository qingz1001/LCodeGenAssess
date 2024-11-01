#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 4
#define MAX_MOVES 1000

typedef struct {
    int board[SIZE][SIZE];
    int moves[MAX_MOVES][4];
    int move_count;
} State;

int is_goal(State *state, int goal[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (state->board[i][j] != goal[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void print_moves(State *state) {
    printf("%d\n", state->move_count);
    for (int i = 0; i < state->move_count; i++) {
        printf("%d%d%d%d\n", state->moves[i][0], state->moves[i][1], state->moves[i][2], state->moves[i][3]);
    }
}

int solve(State *state, int goal[SIZE][SIZE], int depth) {
    if (is_goal(state, goal)) {
        print_moves(state);
        return 1;
    }
    if (depth >= MAX_MOVES) {
        return 0;
    }

    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int d = 0; d < 4; d++) {
                int ni = i + directions[d][0];
                int nj = j + directions[d][1];
                if (ni >= 0 && ni < SIZE && nj >= 0 && nj < SIZE) {
                    swap(&state->board[i][j], &state->board[ni][nj]);
                    state->moves[state->move_count][0] = i;
                    state->moves[state->move_count][1] = j;
                    state->moves[state->move_count][2] = ni;
                    state->moves[state->move_count][3] = nj;
                    state->move_count++;

                    if (solve(state, goal, depth + 1)) {
                        return 1;
                    }

                    state->move_count--;
                    swap(&state->board[i][j], &state->board[ni][nj]);
                }
            }
        }
    }
    return 0;
}

int main() {
    State initial_state;
    int goal[SIZE][SIZE];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            scanf("%d", &initial_state.board[i][j]);
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            scanf("%d", &goal[i][j]);
        }
    }

    initial_state.move_count = 0;
    solve(&initial_state, goal, 0);

    return 0;
}