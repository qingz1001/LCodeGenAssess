#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

int min_switches(int N, int A, int B, int connections[MAX_N][MAX_N], int default_directions[MAX_N]) {
    int visited[MAX_N] = {0};
    int queue[MAX_N];
    int front = 0, rear = 0;
    int switches[MAX_N] = {0};

    queue[rear++] = A - 1;
    visited[A - 1] = 1;

    while (front != rear) {
        int current = queue[front++];
        if (current == B - 1) {
            return switches[current];
        }

        for (int i = 0; i < connections[current][0]; i++) {
            int next = connections[current][i + 1] - 1;
            if (!visited[next]) {
                visited[next] = 1;
                queue[rear++] = next;
                if (default_directions[next] != i + 1) {
                    switches[next] = switches[current] + 1;
                } else {
                    switches[next] = switches[current];
                }
            }
        }
    }

    return -1;
}

int main() {
    int N, A, B;
    scanf("%d %d %d", &N, &A, &B);

    int connections[MAX_N][MAX_N];
    int default_directions[MAX_N];

    for (int i = 0; i < N; i++) {
        scanf("%d", &connections[i][0]);
        for (int j = 1; j <= connections[i][0]; j++) {
            scanf("%d", &connections[i][j]);
        }
        scanf("%d", &default_directions[i]);
    }

    int result = min_switches(N, A, B, connections, default_directions);
    printf("%d\n", result);

    return 0;
}