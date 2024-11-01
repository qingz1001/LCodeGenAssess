#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_N 55
#define MAX_BALLS 1000

int n, max_balls;
int columns[MAX_N][MAX_BALLS];
int column_size[MAX_N];
bool used[MAX_BALLS + 1];

bool is_perfect_square(int num) {
    int i = 1;
    while (i * i < num) i++;
    return i * i == num;
}

void dfs(int ball) {
    if (ball > max_balls) {
        max_balls = ball - 1;
        return;
    }

    for (int i = 0; i < n; i++) {
        if (column_size[i] == 0 || is_perfect_square(columns[i][column_size[i] - 1] + ball)) {
            columns[i][column_size[i]++] = ball;
            used[ball] = true;
            dfs(ball + 1);
            used[ball] = false;
            column_size[i]--;
        }
    }
}

int main() {
    scanf("%d", &n);

    dfs(1);

    printf("%d\n", max_balls);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < column_size[i]; j++) {
            printf("%d ", columns[i][j]);
        }
        printf("\n");
    }

    return 0;
}