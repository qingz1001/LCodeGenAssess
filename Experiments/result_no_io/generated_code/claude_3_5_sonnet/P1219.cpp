#include <stdio.h>
#include <stdbool.h>

#define MAX_N 13

int n;
int queens[MAX_N];
int count = 0;
bool col[MAX_N], diag1[2*MAX_N-1], diag2[2*MAX_N-1];

void printSolution() {
    for (int i = 0; i < n; i++) {
        printf("%d ", queens[i] + 1);
    }
    printf("\n");
}

void solve(int row) {
    if (row == n) {
        count++;
        if (count <= 3) {
            printSolution();
        }
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!col[i] && !diag1[row+i] && !diag2[row-i+n-1]) {
            queens[row] = i;
            col[i] = diag1[row+i] = diag2[row-i+n-1] = true;
            solve(row + 1);
            col[i] = diag1[row+i] = diag2[row-i+n-1] = false;
        }
    }
}

int main() {
    scanf("%d", &n);

    solve(0);

    printf("%d\n", count);

    return 0;
}