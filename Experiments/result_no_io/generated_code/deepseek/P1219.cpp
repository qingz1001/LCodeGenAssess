#include <stdio.h>

#define MAXN 13

int n;
int col[MAXN];
int diag1[2 * MAXN - 1];
int diag2[2 * MAXN - 1];
int solution[MAXN];
int count = 0;

void printSolution() {
    for (int i = 0; i < n; i++) {
        printf("%d ", solution[i] + 1);
    }
    printf("\n");
}

void search(int row) {
    if (row == n) {
        count++;
        if (count <= 3) {
            printSolution();
        }
        return;
    }
    for (int c = 0; c < n; c++) {
        if (col[c] || diag1[row + c] || diag2[row - c + n - 1]) continue;
        col[c] = diag1[row + c] = diag2[row - c + n - 1] = 1;
        solution[row] = c;
        search(row + 1);
        col[c] = diag1[row + c] = diag2[row - c + n - 1] = 0;
    }
}

int main() {
    scanf("%d", &n);
    search(0);
    printf("%d\n", count);
    return 0;
}