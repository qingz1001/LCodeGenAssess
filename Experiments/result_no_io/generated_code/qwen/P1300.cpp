#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_H 30
#define MAX_W 30

typedef struct {
    int x, y;
    char direction;
} Point;

int min(int a, int b) {
    return (a < b) ? a : b;
}

int getCost(char map[MAX_H][MAX_W], int h, int w, Point start, Point end) {
    int cost = 0;
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};
    char directions[] = {'W', 'E', 'N', 'S'};
    int currentDirectionIndex = 0;

    for (int i = start.x, j = start.y; !(i == end.x && j == end.y); ) {
        if (map[i + dx[currentDirectionIndex]][j + dy[currentDirectionIndex]] != '#') {
            i += dx[currentDirectionIndex];
            j += dy[currentDirectionIndex];
            cost++;
        } else {
            int nextDirectionIndex = (currentDirectionIndex + 1) % 4;
            while (nextDirectionIndex != currentDirectionIndex) {
                if (map[i + dx[nextDirectionIndex]][j + dy[nextDirectionIndex]] != '#') {
                    currentDirectionIndex = nextDirectionIndex;
                    break;
                }
                nextDirectionIndex = (nextDirectionIndex + 1) % 4;
            }
            if (nextDirectionIndex == currentDirectionIndex) {
                // Turn around
                cost += 10;
                currentDirectionIndex = (currentDirectionIndex + 2) % 4;
            }
        }
    }

    return cost;
}

int main() {
    int h, w;
    scanf("%d %d", &h, &w);
    char map[MAX_H][MAX_W];

    Point start, end;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            scanf(" %c", &map[i][j]);
            if (map[i][j] == 'E' || map[i][j] == 'W' || map[i][j] == 'N' || map[i][j] == 'S') {
                start.x = i;
                start.y = j;
                start.direction = map[i][j];
            }
            if (map[i][j] == 'F') {
                end.x = i;
                end.y = j;
            }
        }
    }

    printf("%d\n", getCost(map, h, w, start, end));

    return 0;
}