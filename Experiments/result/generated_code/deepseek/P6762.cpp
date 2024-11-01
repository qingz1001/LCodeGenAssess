#include <stdio.h>
#include <string.h>

#define MAX_H 6
#define MAX_W 6

char front[MAX_H][MAX_W];
char side[MAX_H][MAX_W];
int H;

int count_ways(int x, int y, int h, int w) {
    if (x >= h || y >= w) return 0;
    if (front[x][y] == '.' && side[x][y] == '.') return 0;

    int ways = 0;
    // Try placing a 2x2 block
    if (x + 1 < h && y + 1 < w) {
        if (front[x][y] != '.' && front[x][y+1] != '.' && front[x+1][y] != '.' && front[x+1][y+1] != '.') {
            if (side[x][y] != '.' && side[x][y+1] != '.' && side[x+1][y] != '.' && side[x+1][y+1] != '.') {
                ways++;
            }
        }
    }

    // Try placing a 1x1 block
    if (front[x][y] != '.' && side[x][y] != '.') {
        ways++;
    }

    // Recursively count ways for the next position
    ways += count_ways(x, y + 1, h, w);
    ways += count_ways(x + 1, y, h, w);

    return ways;
}

int main() {
    scanf("%d", &H);
    for (int i = 0; i < H; i++) {
        scanf("%s", front[i]);
    }
    for (int i = 0; i < H; i++) {
        scanf("%s", side[i]);
    }

    int ways = count_ways(0, 0, H, 6);
    printf("%d\n", ways);

    return 0;
}