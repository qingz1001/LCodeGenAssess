#include <stdio.h>
#include <stdbool.h>

#define MAX_N 13

int n;
int col[MAX_N + 1];
int count = 0;

bool check(int row, int column) {
    for (int i = 1; i < row; i++) {
        if (col[i] == column || 
            abs(col[i] - column) == abs(i - row)) {
            return false;
        }
    }
    return true;
}

void dfs(int row) {
    if (row > n) {
        count++;
        if (count <= 3) {
            for (int i = 1; i <= n; i++) {
                printf("%d ", col[i]);
            }
            printf("\n");
        }
        return;
    }
    
    for (int i = 1; i <= n; i++) {
        if (check(row, i)) {
            col[row] = i;
            dfs(row + 1);
        }
    }
}

int main() {
    scanf("%d", &n);
    dfs(1);
    printf("%d\n", count);
    return 0;
}