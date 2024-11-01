#include <stdio.h>
#include <stdlib.h>

#define MAX_R 50
#define MAX_C 50
#define MAX_N 100

int grid[MAX_R][MAX_C];
int n, r, c;
int cows[MAX_N];

void mark_path(int x, int y) {
    while (x >= 0 && y < c) {
        grid[x--][y++] = -1;
    }
}

int is_safe() {
    for (int i = 0; i < n; i++) {
        int x = cows[i] / c;
        int y = cows[i] % c;
        mark_path(x, y);
    }
    for (int i = 0; i < n; i++) {
        int x = cows[i] / c;
        int y = cows[i] % c;
        if (grid[x][y] == -1) return 0;
    }
    return 1;
}

int main() {
    scanf("%d %d", &r, &c);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &cows[i], &cows[i]);
        cows[i]--;
    }

    if (is_safe()) {
        printf("0\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        int original_x = cows[i] / c;
        int original_y = cows[i] % c;
        grid[original_x][original_y] = 0;

        cows[i] = -1;
        if (!is_safe()) {
            printf("%d\n", i + 1);
        }

        cows[i] = original_x * c + original_y;
        grid[original_x][original_y] = 1;
    }

    return 0;
}