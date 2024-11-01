#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200

int N, A, B;
int K[MAXN + 1];
int visited[MAXN + 1];

typedef struct {
    int floor;
    int steps;
} Node;

int bfs() {
    Node queue[MAXN * MAXN];
    int front = 0, rear = 0;
    queue[rear++] = (Node){A, 0};
    visited[A] = 1;

    while (front < rear) {
        Node current = queue[front++];
        int current_floor = current.floor;
        int current_steps = current.steps;

        if (current_floor == B) {
            return current_steps;
        }

        int next_up = current_floor + K[current_floor];
        int next_down = current_floor - K[current_floor];

        if (next_up <= N && !visited[next_up]) {
            queue[rear++] = (Node){next_up, current_steps + 1};
            visited[next_up] = 1;
        }

        if (next_down >= 1 && !visited[next_down]) {
            queue[rear++] = (Node){next_down, current_steps + 1};
            visited[next_down] = 1;
        }
    }

    return -1;
}

int main() {
    scanf("%d %d %d", &N, &A, &B);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &K[i]);
    }

    int result = bfs();
    printf("%d\n", result);

    return 0;
}