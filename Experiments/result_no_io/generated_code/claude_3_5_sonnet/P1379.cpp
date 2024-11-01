#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STATES 362880
#define TARGET_STATE 123804765

typedef struct {
    int board[9];
    int zero_pos;
    int steps;
} State;

int visited[MAX_STATES];
State queue[MAX_STATES];
int front = 0, rear = 0;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int factorial(int n) {
    return (n == 0 || n == 1) ? 1 : n * factorial(n - 1);
}

int cantor(int board[]) {
    int result = 0;
    for (int i = 0; i < 9; i++) {
        int cnt = 0;
        for (int j = i + 1; j < 9; j++) {
            if (board[j] < board[i]) cnt++;
        }
        result += cnt * factorial(8 - i);
    }
    return result;
}

int bfs(State initial) {
    queue[rear++] = initial;
    visited[cantor(initial.board)] = 1;

    while (front < rear) {
        State curr = queue[front++];

        if (cantor(curr.board) == TARGET_STATE) {
            return curr.steps;
        }

        int x = curr.zero_pos / 3;
        int y = curr.zero_pos % 3;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
                State next = curr;
                next.zero_pos = nx * 3 + ny;
                next.board[curr.zero_pos] = next.board[next.zero_pos];
                next.board[next.zero_pos] = 0;
                next.steps++;

                int cantor_value = cantor(next.board);
                if (!visited[cantor_value]) {
                    visited[cantor_value] = 1;
                    queue[rear++] = next;
                }
            }
        }
    }

    return -1;
}

int main() {
    State initial;
    for (int i = 0; i < 9; i++) {
        scanf("%d", &initial.board[i]);
        if (initial.board[i] == 0) {
            initial.zero_pos = i;
        }
    }
    initial.steps = 0;

    int result = bfs(initial);
    printf("%d\n", result);

    return 0;
}