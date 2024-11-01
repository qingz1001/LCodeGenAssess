#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MOVES 30

typedef struct {
    int board[9];
    int zero_index;
} State;

int heuristic(int *board) {
    int count = 0;
    for (int i = 0; i < 9; ++i) {
        if (board[i] != 0 && board[i] != i + 1) {
            count++;
        }
    }
    return count;
}

void print_board(int *board) {
    for (int i = 0; i < 9; ++i) {
        printf("%d ", board[i]);
        if ((i + 1) % 3 == 0) printf("\n");
    }
}

int is_goal(int *board) {
    for (int i = 0; i < 9; ++i) {
        if (board[i] != i + 1 && board[i] != 0) return 0;
    }
    return 1;
}

int get_zero_index(int *board) {
    for (int i = 0; i < 9; ++i) {
        if (board[i] == 0) return i;
    }
    return -1;
}

State move(State current, int direction) {
    State next = current;
    int zero_index = current.zero_index;
    int new_index;

    switch (direction) {
        case 0: // up
            new_index = zero_index - 3;
            break;
        case 1: // down
            new_index = zero_index + 3;
            break;
        case 2: // left
            new_index = zero_index - 1;
            break;
        case 3: // right
            new_index = zero_index + 1;
            break;
        default:
            return current;
    }

    if (new_index >= 0 && new_index < 9) {
        next.board[zero_index] = next.board[new_index];
        next.board[new_index] = 0;
        next.zero_index = new_index;
    }

    return next;
}

int solve(State start) {
    int visited[1000000] = {0};
    State queue[MAX_MOVES];
    int front = 0, rear = 0;
    queue[rear++] = start;

    while (front < rear) {
        State current = queue[front++];
        if (is_goal(current.board)) {
            return current.moves;
        }
        if (!visited[current.hash]) {
            visited[current.hash] = 1;
            for (int i = 0; i < 4; ++i) {
                State next = move(current, i);
                next.moves = current.moves + 1;
                next.hash = next.moves * 1000000 + next.zero_index;
                queue[rear++] = next;
            }
        }
    }

    return -1;
}

int main() {
    char input[10];
    scanf("%s", input);

    State start;
    for (int i = 0; i < 9; ++i) {
        start.board[i] = input[i] - '0';
        if (start.board[i] == 0) start.zero_index = i;
    }

    start.moves = 0;
    start.hash = start.moves * 1000000 + start.zero_index;

    printf("%d\n", solve(start));

    return 0;
}