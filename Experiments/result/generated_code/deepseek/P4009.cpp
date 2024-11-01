#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100
#define MAXK 10

typedef struct {
    int x, y, fuel, cost;
} State;

int N, K, A, B, C;
int grid[MAXN][MAXN];
int visited[MAXN][MAXN][MAXK + 1];

int min(int a, int b) {
    return a < b ? a : b;
}

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int compare(const void *a, const void *b) {
    return ((State *)a)->cost - ((State *)b)->cost;
}

int dijkstra() {
    State queue[MAXN * MAXN * (MAXK + 1)];
    int front = 0, rear = 0;
    queue[rear++] = (State){0, 0, K, 0};
    visited[0][0][K] = 0;

    while (front < rear) {
        State current = queue[front++];
        int x = current.x, y = current.y, fuel = current.fuel, cost = current.cost;

        if (x == N - 1 && y == N - 1) return cost;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;

            int new_fuel = fuel - 1;
            int new_cost = cost;

            if (i == 1 || i == 3) new_cost += B; // Moving left or up

            if (new_fuel < 0) continue;

            if (grid[nx][ny] == 1) {
                new_fuel = K;
                new_cost += A;
            }

            if (visited[nx][ny][new_fuel] > new_cost) {
                visited[nx][ny][new_fuel] = new_cost;
                queue[rear++] = (State){nx, ny, new_fuel, new_cost};
            }
        }

        if (fuel < K) {
            int new_fuel = K;
            int new_cost = cost + C;

            if (visited[x][y][new_fuel] > new_cost) {
                visited[x][y][new_fuel] = new_cost;
                queue[rear++] = (State){x, y, new_fuel, new_cost};
            }
        }

        qsort(queue + front, rear - front, sizeof(State), compare);
    }

    return -1;
}

int main() {
    scanf("%d %d %d %d %d", &N, &K, &A, &B, &C);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
            for (int k = 0; k <= K; k++) {
                visited[i][j][k] = INT_MAX;
            }
        }
    }

    int result = dijkstra();
    printf("%d\n", result);

    return 0;
}