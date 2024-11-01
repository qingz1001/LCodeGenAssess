#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_R 40
#define MAX_C 26

typedef struct {
    int r, c;
} Position;

int abs(int x) {
    return (x < 0) ? -x : x;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int king_to_knight(Position k, Position* knights, int num_knights) {
    int min_steps = INT_MAX;
    for (int i = 0; i < num_knights; i++) {
        int steps = abs(k.r - knights[i].r) + abs(k.c - knights[i].c);
        if (steps < min_steps) {
            min_steps = steps;
        }
    }
    return min_steps;
}

int knight_to_knight(Position* knights, int num_knights) {
    int min_steps = INT_MAX;
    for (int i = 0; i < num_knights; i++) {
        for (int j = i + 1; j < num_knights; j++) {
            int steps = abs(knights[i].r - knights[j].r) + abs(knights[i].c - knights[j].c);
            if (steps < min_steps) {
                min_steps = steps;
            }
        }
    }
    return min_steps;
}

int main() {
    int R, C;
    scanf("%d %d", &R, &C);

    char board[MAX_R][MAX_C + 1];
    for (int i = 0; i < R; i++) {
        scanf("%s", board[i]);
    }

    Position king;
    Position knights[MAX_R * MAX_C];
    int num_knights = 0;

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (board[i][j] == 'K') {
                king.r = i;
                king.c = j;
            } else if (board[i][j] >= '1' && board[i][j] <= '9') {
                knights[num_knights].r = i;
                knights[num_knights].c = j;
                num_knights++;
            }
        }
    }

    int total_steps = king_to_knight(king, knights, num_knights);
    for (int i = 0; i < num_knights; i++) {
        total_steps += king_to_knight(knights[i], knights, num_knights);
    }

    printf("%d\n", total_steps);

    return 0;
}