#include <stdio.h>
#include <stdbool.h>

#define MAX_R 50
#define MAX_C 50
#define MAX_N 100

typedef struct {
    int x, y;
} Cow;

Cow cows[MAX_N];
bool grid[MAX_R][MAX_C];
int r, c, n;

bool is_safe(int x, int y) {
    for (int i = 0; i < n; i++) {
        if (cows[i].x == x && cows[i].y == y) continue;
        if (cows[i].x <= x && cows[i].y <= y) return false;
    }
    return true;
}

int main() {
    scanf("%d %d", &r, &c);
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &cows[i].x, &cows[i].y);
        cows[i].x--;
        cows[i].y--;
        grid[cows[i].x][cows[i].y] = true;
    }

    bool all_safe = true;
    for (int i = 0; i < n; i++) {
        if (!is_safe(cows[i].x, cows[i].y)) {
            all_safe = false;
            break;
        }
    }

    if (all_safe) {
        printf("0\n");
        return 0;
    }

    bool can_be_safe = false;
    for (int i = 0; i < n; i++) {
        grid[cows[i].x][cows[i].y] = false;
        bool safe = true;
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if (!is_safe(cows[j].x, cows[j].y)) {
                safe = false;
                break;
            }
        }
        if (safe) {
            printf("%d\n", i + 1);
            can_be_safe = true;
        }
        grid[cows[i].x][cows[i].y] = true;
    }

    if (!can_be_safe) {
        printf("-1\n");
    }

    return 0;
}