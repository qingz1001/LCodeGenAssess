#include <stdio.h>
#include <stdbool.h>

#define N 13

int n, solutions[10];
bool col[N], diag1[N * 2], diag2[N * 2];

void backtrack(int row) {
    if (row == n) {
        for (int i = 0; i < n; i++) {
            printf("%d ", solutions[i]);
        }
        printf("\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        int id1 = row + i, id2 = n - 1 + row - i;
        if (!col[i] && !diag1[id1] && !diag2[id2]) {
            col[i] = diag1[id1] = diag2[id2] = true;
            solutions[row] = i + 1;
            backtrack(row + 1);
            col[i] = diag1[id1] = diag2[id2] = false;
        }
    }
}

int main() {
    scanf("%d", &n);
    backtrack(0);
    return 0;
}