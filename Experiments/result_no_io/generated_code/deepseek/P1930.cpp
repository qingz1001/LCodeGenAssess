#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX_R 40
#define MAX_C 26
#define MAX_KNIGHTS 64

typedef struct {
    int x, y;
} Point;

int R, C;
Point king, knights[MAX_KNIGHTS];
int knight_count = 0;

int knight_moves[8][2] = {
    {-2, -1}, {-1, -2}, {1, -2}, {2, -1},
    {2, 1}, {1, 2}, {-1, 2}, {-2, 1}
};

int min(int a, int b) {
    return a < b ? a : b;
}

int abs(int x) {
    return x < 0 ? -x : x;
}

int king_distance(int x, int y) {
    return max(abs(king.x - x), abs(king.y - y));
}

int knight_distance(int x1, int y1, int x2, int y2) {
    if (x1 == x2 && y1 == y2) return 0;
    int queue[MAX_R * MAX_C][2];
    int head = 0, tail = 0;
    int visited[MAX_R][MAX_C];
    memset(visited, 0, sizeof(visited));
    queue[tail][0] = x1;
    queue[tail][1] = y1;
    tail++;
    visited[x1][y1] = 1;
    int steps = 0;
    while (head < tail) {
        int size = tail - head;
        for (int i = 0; i < size; i++) {
            int cx = queue[head][0];
            int cy = queue[head][1];
            head++;
            if (cx == x2 && cy == y2) return steps;
            for (int j = 0; j < 8; j++) {
                int nx = cx + knight_moves[j][0];
                int ny = cy + knight_moves[j][1];
                if (nx >= 0 && nx < R && ny >= 0 && ny < C && !visited[nx][ny]) {
                    visited[nx][ny] = 1;
                    queue[tail][0] = nx;
                    queue[tail][1] = ny;
                    tail++;
                }
            }
        }
        steps++;
    }
    return INT_MAX;
}

int main() {
    scanf("%d %d", &R, &C);
    char col;
    int row;
    scanf(" %c%d", &col, &row);
    king.x = row - 1;
    king.y = col - 'A';
    while (scanf(" %c%d", &col, &row) != EOF) {
        knights[knight_count].x = row - 1;
        knights[knight_count].y = col - 'A';
        knight_count++;
    }

    int min_steps = INT_MAX;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            int total_steps = 0;
            for (int k = 0; k < knight_count; k++) {
                total_steps += knight_distance(knights[k].x, knights[k].y, i, j);
            }
            int king_steps = king_distance(i, j);
            for (int k = 0; k < knight_count; k++) {
                int combined_steps = total_steps - knight_distance(knights[k].x, knights[k].y, i, j);
                combined_steps += knight_distance(king.x, king.y, knights[k].x, knights[k].y);
                combined_steps += knight_distance(knights[k].x, knights[k].y, i, j);
                king_steps = min(king_steps, combined_steps);
            }
            total_steps += king_steps;
            min_steps = min(min_steps, total_steps);
        }
    }

    printf("%d\n", min_steps);
    return 0;
}