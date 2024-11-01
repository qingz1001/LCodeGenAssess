#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4

typedef struct Node {
    int board[N][N];
    int moves;
    int parent;
    int from;
    int to;
} Node;

Node queue[1000000];
int front = 0;
int rear = 0;

int is_goal(Node *current, Node *goal) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (current->board[i][j] != goal->board[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

void enqueue(Node *current, Node *parent, int from, int to) {
    memcpy(current->board, parent->board, sizeof(parent->board));
    current->board[from / N][from % N] = parent->board[to / N][to % N];
    current->board[to / N][to % N] = parent->board[from / N][from % N];
    current->moves = parent->moves + 1;
    current->parent = parent - queue;
    current->from = from;
    current->to = to;
    queue[rear++] = *current;
}

int bfs(Node *start, Node *goal) {
    queue[front++] = *start;
    while (front < rear) {
        Node *current = &queue[front++];
        if (is_goal(current, goal)) {
            return current->moves;
        }
        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < 4; k++) {
                    int ni = i + directions[k][0];
                    int nj = j + directions[k][1];
                    if (ni >= 0 && ni < N && nj >= 0 && nj < N) {
                        enqueue(&queue[rear], current, i * N + j, ni * N + nj);
                    }
                }
            }
        }
    }
    return -1;
}

int main() {
    Node start, goal;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%1d", &start.board[i][j]);
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%1d", &goal.board[i][j]);
        }
    }
    int steps = bfs(&start, &goal);
    if (steps == -1) {
        printf("No solution found.\n");
    } else {
        printf("%d\n", steps);
        Node *current = &queue[rear - 1];
        while (current->parent != -1) {
            printf("%d%d%d%d\n", current->from / N + 1, current->from % N + 1, current->to / N + 1, current->to % N + 1);
            current = &queue[current->parent];
        }
    }
    return 0;
}