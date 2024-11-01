#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX_R 40
#define MAX_C 26

typedef struct {
    int x, y;
} Point;

int R, C;
Point king, knights[MAX_R * MAX_C];
int knight_count = 0;

int knight_moves[8][2] = {{-2, -1}, {-1, -2}, {1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, 1}};

int min(int a, int b) {
    return a < b ? a : b;
}

int abs(int x) {
    return x < 0 ? -x : x;
}

int king_distance(Point a, Point b) {
    return max(abs(a.x - b.x), abs(a.y - b.y));
}

int knight_distance(Point a, Point b) {
    int dx = abs(a.x - b.x);
    int dy = abs(a.y - b.y);
    if (dx > dy) {
        int temp = dx;
        dx = dy;
        dy = temp;
    }
    if (dx == 1 && dy == 2) return 1;
    if (dx == 0 && dy == 0) return 0;
    return 2;
}

int main() {
    scanf("%d %d", &R, &C);
    char col;
    int row;
    scanf(" %c %d", &col, &row);
    king.x = row - 1;
    king.y = col - 'A';

    while (scanf(" %c %d", &col, &row) != EOF) {
        knights[knight_count].x = row - 1;
        knights[knight_count].y = col - 'A';
        knight_count++;
    }

    int min_steps = INT_MAX;

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            Point target = {i, j};
            int total_steps = 0;

            for (int k = 0; k < knight_count; k++) {
                total_steps += knight_distance(knights[k], target);
            }

            int king_steps = king_distance(king, target);
            int combined_steps = total_steps + king_steps;

            for (int k = 0; k < knight_count; k++) {
                int knight_to_king = knight_distance(knights[k], king);
                int new_total_steps = total_steps - knight_distance(knights[k], target) + knight_to_king;
                combined_steps = min(combined_steps, new_total_steps);
            }

            min_steps = min(min_steps, combined_steps);
        }
    }

    printf("%d\n", min_steps);

    return 0;
}