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
Node queue[1 << 16];
bool visited[1 << 16];
int front, rear;

int encode(State *s) {
    int code = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            code = (code << 1) | s->board[i][j];
        }
    }
    return code;
}

bool is_valid(int x, int y) {
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}

bool is_goal(State *s) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (s->board[i][j] != target.board[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void bfs() {
    front = rear = 0;
    queue[rear++] = (Node){initial, 0};
    visited[encode(&initial)] = true;

    while (front < rear) {
        Node current = queue[front++];

        if (is_goal(&current.state)) {
            printf("%d\n", current.steps);
            for (int i = 0; i < current.steps; i++) {
                printf("%d %d %d %d\n", current.moves[i].x1 + 1, current.moves[i].y1 + 1,
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
                        next.state.board[i][j] ^= 1;
                        next.state.board[ni][nj] ^= 1;
                        next.steps++;
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

    printf("No solution\n");
}

int main() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            scanf("%d", &initial.board[i][j]);
        }
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            scanf("%d", &target.board[i][j]);
        }
    }

    bfs();

    return 0;
}