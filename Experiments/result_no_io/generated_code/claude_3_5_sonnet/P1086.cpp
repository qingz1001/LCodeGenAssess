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
} Cell;

Cell cells[MAX_M * MAX_N];
int cell_count = 0;

int cmp(const void *a, const void *b) {
    return ((Cell *)b)->peanuts - ((Cell *)a)->peanuts;
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
    
    if (field[row][col] > 0) {
        dfs(row, col, time + 1, peanuts + field[row][col]);
    } else {
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        
        for (int i = 0; i < 4; i++) {
            int new_row = row + dx[i];
            int new_col = col + dy[i];
            dfs(new_row, new_col, time + 1, peanuts);
        }
    }

    visited[row][col] = 0;
}

int main() {
    scanf("%d %d %d", &M, &N, &K);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &field[i][j]);
            if (field[i][j] > 0) {
                cells[cell_count].row = i;
                cells[cell_count].col = j;
                cells[cell_count].peanuts = field[i][j];
                cell_count++;
            }
        }
    }

    qsort(cells, cell_count, sizeof(Cell), cmp);

    for (int i = 0; i < cell_count; i++) {
        int start_row = cells[i].row;
        int start_col = cells[i].col;
        int initial_time = start_row + 1;

        if (initial_time <= K) {
            dfs(start_row, start_col, initial_time, 0);
        }
    }

    printf("%d\n", max_peanuts);

    return 0;
}