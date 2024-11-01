#include <stdio.h>
#include <stdlib.h>

#define MAX_M 20
#define MAX_N 20

int M, N, K;
int field[MAX_M][MAX_N];
int visited[MAX_M][MAX_N];
int max_peanuts = 0;

typedef struct {
    int row;
    int col;
    int peanuts;
} Plant;

Plant plants[MAX_M * MAX_N];
int plant_count = 0;

int compare(const void *a, const void *b) {
    return ((Plant *)b)->peanuts - ((Plant *)a)->peanuts;
}

void dfs(int row, int col, int time, int peanuts) {
    if (time > K || row < 0 || row >= M || col < 0 || col >= N || visited[row][col]) {
        return;
    }

    if (row == 0) {
        if (peanuts > max_peanuts) {
            max_peanuts = peanuts;
        }
    }

    visited[row][col] = 1;

    dfs(row - 1, col, time + 1, peanuts);
    dfs(row + 1, col, time + 1, peanuts);
    dfs(row, col - 1, time + 1, peanuts);
    dfs(row, col + 1, time + 1, peanuts);

    if (field[row][col] > 0) {
        dfs(row - 1, col, time + 2, peanuts + field[row][col]);
        dfs(row + 1, col, time + 2, peanuts + field[row][col]);
        dfs(row, col - 1, time + 2, peanuts + field[row][col]);
        dfs(row, col + 1, time + 2, peanuts + field[row][col]);
    }

    visited[row][col] = 0;
}

int main() {
    scanf("%d %d %d", &M, &N, &K);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &field[i][j]);
            if (field[i][j] > 0) {
                plants[plant_count].row = i;
                plants[plant_count].col = j;
                plants[plant_count].peanuts = field[i][j];
                plant_count++;
            }
        }
    }

    qsort(plants, plant_count, sizeof(Plant), compare);

    for (int i = 0; i < plant_count; i++) {
        if (plants[i].row == 0) {
            dfs(plants[i].row, plants[i].col, 2, plants[i].peanuts);
        } else {
            dfs(plants[i].row, plants[i].col, 3, plants[i].peanuts);
        }
    }

    printf("%d\n", max_peanuts);

    return 0;
}