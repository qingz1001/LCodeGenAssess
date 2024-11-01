#include <stdio.h>
#include <stdlib.h>

#define MAX_N 56
#define MAX_SQ 31623 // sqrt(55^2 * 2) = 31623

int is_perfect_square(int num) {
    int root = (int)sqrt(num);
    return root * root == num;
}

int dfs(int n, int col, int *stack, int *max_balls, int **solution) {
    if (col >= n) {
        return stack[0];
    }

    int max_balls_col = 0;
    for (int i = 1; i <= MAX_N; i++) {
        if (!is_perfect_square(stack[col] + i)) continue;

        stack[col + 1] = i;
        int balls_in_col = dfs(n, col + 1, stack, &max_balls_col, solution);
        if (balls_in_col > *max_balls) {
            *max_balls = balls_in_col;
            for (int j = 0; j <= col; j++) {
                solution[j][col] = stack[j];
            }
        }
    }

    return *max_balls;
}

int main() {
    int n;
    scanf("%d", &n);

    int stack[MAX_N];
    int max_balls = 0;
    int **solution = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        solution[i] = (int *)malloc(MAX_N * sizeof(int));
    }

    stack[0] = 1;
    dfs(n, 0, stack, &max_balls, solution);

    printf("%d\n", max_balls);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            printf("%d ", solution[j][i]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        free(solution[i]);
    }
    free(solution);

    return 0;
}