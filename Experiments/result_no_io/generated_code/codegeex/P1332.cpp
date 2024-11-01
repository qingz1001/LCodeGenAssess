#include <stdio.h>
#include <stdlib.h>

#define MAXN 501
#define MAXA 100001

int matrix[MAXN][MAXN];
int n, m, a, b;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

typedef struct {
    int x, y;
} Position;

typedef struct {
    Position pos;
    int time;
} QueueElement;

void BFS() {
    QueueElement queue[MAXA];
    int front = 0, rear = 0;

    // Initialize the queue with all initial infection sources
    for (int i = 1; i <= a; i++) {
        queue[rear].pos.x = matrix[i][0];
        queue[rear].pos.y = matrix[i][1];
        queue[rear].time = 0;
        rear++;
    }

    while (front < rear) {
        QueueElement current = queue[front];
        front++;

        for (int i = 0; i < 4; i++) {
            int nx = current.pos.x + dx[i];
            int ny = current.pos.y + dy[i];

            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && matrix[nx][ny] == 0) {
                matrix[nx][ny] = 1;
                queue[rear].pos.x = nx;
                queue[rear].pos.y = ny;
                queue[rear].time = current.time + 1;
                rear++;
            }
        }
    }
}

int main() {
    scanf("%d %d %d %d", &n, &m, &a, &b);
    int *infectionSources = (int *)malloc(2 * a * sizeof(int));
    int *leaders = (int *)malloc(2 * b * sizeof(int));

    // Read infection sources
    for (int i = 0; i < 2 * a; i += 2) {
        scanf("%d %d", &infectionSources[i], &infectionSources[i + 1]);
        matrix[infectionSources[i]][infectionSources[i + 1]] = 1;
    }

    // Read leaders
    for (int i = 0; i < 2 * b; i += 2) {
        scanf("%d %d", &leaders[i], &leaders[i + 1]);
    }

    // Perform BFS to find infection times
    BFS();

    // Output the infection times for the leaders
    for (int i = 0; i < 2 * b; i += 2) {
        int x = leaders[i];
        int y = leaders[i + 1];
        printf("%d\n", matrix[x][y]);
    }

    free(infectionSources);
    free(leaders);

    return 0;
}