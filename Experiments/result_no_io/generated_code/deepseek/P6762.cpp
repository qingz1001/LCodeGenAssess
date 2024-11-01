#include <stdio.h>
#include <stdbool.h>

#define MAX_H 6
#define MAX_W 6

char front[MAX_H][MAX_W];
char side[MAX_H][MAX_W];
int H;

bool is_valid_placement(int x, int y) {
    if (x < 0 || x >= H || y < 0 || y >= 6) return false;
    return true;
}

bool check_placement(int x, int y, int dx, int dy) {
    if (!is_valid_placement(x + dx, y + dy)) return false;
    if (front[x][y] == 'W' || front[x + dx][y + dy] == 'W') return false;
    if (side[x][y] == 'W' || side[x + dx][y + dy] == 'W') return false;
    return true;
}

int count_placements() {
    int count = 0;
    for (int x = 0; x < H; x++) {
        for (int y = 0; y < 6; y++) {
            if (check_placement(x, y, 0, 1)) count++; // Horizontal placement
            if (check_placement(x, y, 1, 0)) count++; // Vertical placement
        }
    }
    return count;
}

int main() {
    scanf("%d", &H);
    for (int i = 0; i < H; i++) {
        scanf("%s", front[i]);
    }
    for (int i = 0; i < H; i++) {
        scanf("%s", side[i]);
    }

    int result = count_placements();
    printf("%d\n", result);

    return 0;
}