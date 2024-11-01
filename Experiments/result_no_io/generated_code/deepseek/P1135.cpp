#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200
#define INF 0x3f3f3f3f

int N, A, B;
int K[MAXN + 1];
int dist[MAXN + 1];

typedef struct {
    int floor;
    int steps;
} Node;

int bfs() {
    if (A == B) return 0;

    Node queue[MAXN];
    int front = 0, rear = 0;
    queue[rear++] = (Node){A, 0};
    memset(dist, INF, sizeof(dist));
    dist[A] = 0;

    while (front < rear) {
        Node current = queue[front++];
        int currentFloor = current.floor;
        int currentSteps = current.steps;

        // Move up
        int nextFloor = currentFloor + K[currentFloor];
        if (nextFloor <= N && dist[nextFloor] == INF) {
            if (nextFloor == B) return currentSteps + 1;
            dist[nextFloor] = currentSteps + 1;
            queue[rear++] = (Node){nextFloor, currentSteps + 1};
        }

        // Move down
        nextFloor = currentFloor - K[currentFloor];
        if (nextFloor >= 1 && dist[nextFloor] == INF) {
            if (nextFloor == B) return currentSteps + 1;
            dist[nextFloor] = currentSteps + 1;
            queue[rear++] = (Node){nextFloor, currentSteps + 1};
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