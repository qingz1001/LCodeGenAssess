#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STEPS 16
#define BOARD_SIZE 4

typedef struct {
    int board[BOARD_SIZE][BOARD_SIZE];
} State;

typedef struct {
    int x1, y1, x2, y2;
} Move;

typedef struct {
    State state;
    int steps;
    Move moves[MAX_STEPS];
} Node;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

State initial, target;
Node queue[1000000];
int front = 0, rear = 0;

bool visited[65536];

int encode(State* state) {
    int code = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            code = (code << 1) | state->board[i][j];
        }
    }
    return code;
}

void decode(int code, State* state) {
    for (int i = BOARD_SIZE - 1; i >= 0; i--) {
        for (int j = BOARD_SIZE - 1; j >= 0; j--) {
            state->board[i][j] = code & 1;
            code >>= 1;
        }
    }
}

bool is_equal(State* a, State* b) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (a->board[i][j] != b->board[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool is_valid(int x, int y) {
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bfs() {
    queue[rear++] = (Node){initial, 0};
    visited[encode(&initial)] = true;

    while (front < rear) {
        Node current = queue[front++];

        if (is_equal(&current.state, &target)) {
            printf("%d\n", current.steps);
            for (int i = 0; i < current.steps; i++) {
                printf("%d%d%d%d\n", current.moves[i].x1 + 1, current.moves[i].y1 + 1,
                       current.moves[i].x2 + 1, current.moves[i].y2 + 1);
            }
            return;
        }

        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                for (int k = 0; k < 4; k++) {
                    int ni = i + dx[k];
                    int nj = j + dy[k];

                    if (is_valid(ni, nj)) {
                        Node next = current;
                        next.steps++;
                        swap(&next.state.board[i][j], &next.state.board[ni][nj]);
                        next.moves[next.steps - 1] = (Move){i, j, ni, nj};

                        int code = encode(&next.state);
                        if (!visited[code]) {
                            visited[code] = true;
                            queue[rear++] = next;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            scanf("%1d", &initial.board[i][j]);
        }
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            scanf("%1d", &target.board[i][j]);
        }
    }

    bfs();

    return 0;
}