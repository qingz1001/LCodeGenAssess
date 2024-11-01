#include <stdio.h>
#include <stdbool.h>

#define N 4
#define TARGET 34

int grid[N][N];
bool used[N * N + 1];

bool check_sum(int x1, int y1, int x2, int y2) {
    int sum = 0;
    for (int i = x1; i <= x2; i++) {
        for (int j = y1; j <= y2; j++) {
            sum += grid[i][j];
        }
    }
    return sum == TARGET;
}

bool check_all() {
    // Check rows
    for (int i = 0; i < N; i++) {
        if (!check_sum(i, 0, i, N - 1)) return false;
    }
    // Check columns
    for (int j = 0; j < N; j++) {
        if (!check_sum(0, j, N - 1, j)) return false;
    }
    // Check main diagonal
    if (!check_sum(0, 0, N - 1, N - 1)) return false;
    // Check secondary diagonal
    if (!check_sum(0, N - 1, N - 1, 0)) return false;
    // Check corners
    if (!check_sum(0, 0, 0, 0) + check_sum(0, N - 1, 0, N - 1) + check_sum(N - 1, 0, N - 1, 0) + check_sum(N - 1, N - 1, N - 1, N - 1) != TARGET) return false;
    // Check 2x2 corners
    if (!check_sum(0, 0, 1, 1) || !check_sum(0, N - 2, 1, N - 1) || !check_sum(N - 2, 0, N - 1, 1) || !check_sum(N - 2, N - 2, N - 1, N - 1)) return false;
    // Check center 2x2
    if (!check_sum(1, 1, 2, 2)) return false;
    return true;
}

void print_solution() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void solve(int x, int y) {
    if (x == N) {
        if (check_all()) {
            print_solution();
        }
        return;
    }

    int next_x = x, next_y = y + 1;
    if (next_y == N) {
        next_x++;
        next_y = 0;
    }

    if (grid[x][y] != 0) {
        solve(next_x, next_y);
        return;
    }

    for (int num = 2; num <= N * N; num++) {
        if (!used[num]) {
            grid[x][y] = num;
            used[num] = true;
            solve(next_x, next_y);
            grid[x][y] = 0;
            used[num] = false;
        }
    }
}

int main() {
    int i, j;
    scanf("%d %d", &i, &j);
    i--; j--;
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            grid[x][y] = 0;
        }
    }
    grid[i][j] = 1;
    used[1] = true;
    solve(0, 0);
    return 0;
}