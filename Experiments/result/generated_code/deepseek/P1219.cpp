#include <stdio.h>

#define MAXN 13

int n;
int col[MAXN];
int diag1[2 * MAXN - 1];
int diag2[2 * MAXN - 1];
int solutions[MAXN][MAXN];
int solution_count = 0;

void print_solution() {
    if (solution_count < 3) {
        for (int i = 0; i < n; i++) {
            printf("%d ", col[i] + 1);
        }
        printf("\n");
    }
    solution_count++;
}

void solve(int row) {
    if (row == n) {
        print_solution();
        return;
    }
    for (int c = 0; c < n; c++) {
        if (!col[c] && !diag1[row + c] && !diag2[row - c + n - 1]) {
            col[c] = 1;
            diag1[row + c] = 1;
            diag2[row - c + n - 1] = 1;
            solve(row + 1);
            col[c] = 0;
            diag1[row + c] = 0;
            diag2[row - c + n - 1] = 0;
        }
    }
}

int main() {
    scanf("%d", &n);
    solve(0);
    printf("%d\n", solution_count);
    return 0;
}