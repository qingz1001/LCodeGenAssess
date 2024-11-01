#include <stdio.h>
#include <stdbool.h>

#define MAX_R 50
#define MAX_C 50
#define MAX_N 100

int r, c, n;
int cow[MAX_N][2];
bool map[MAX_R][MAX_C];

bool is_safe(int exclude) {
    bool occupied[MAX_R][MAX_C] = {0};
    for (int i = 0; i < n; i++) {
        if (i == exclude) continue;
        int x = cow[i][0] - 1, y = cow[i][1] - 1;
        occupied[x][y] = true;
    }

    for (int i = 0; i < n; i++) {
        if (i == exclude) continue;
        int x = cow[i][0] - 1, y = cow[i][1] - 1;
        while (x >= 0 && y < c) {
            if (occupied[x][y] && (x != cow[i][0] - 1 || y != cow[i][1] - 1)) {
                return false;
            }
            if (x > 0) x--;
            else y++;
        }
    }
    return true;
}

int main() {
    scanf("%d %d", &r, &c);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &cow[i][0], &cow[i][1]);
    }

    if (is_safe(-1)) {
        printf("0\n");
        return 0;
    }

    bool found = false;
    for (int i = 0; i < n; i++) {
        if (is_safe(i)) {
            printf("%d\n", i + 1);
            found = true;
        }
    }

    if (!found) {
        printf("-1\n");
    }

    return 0;
}