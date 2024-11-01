#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000

typedef struct {
    int x1, y1, x2, y2;
} Line;

Line lines[MAXN];
int moves[MAXN][2];
int n;

int check_collision(int idx, int direction) {
    Line *line = &lines[idx];
    int new_x1, new_y1, new_x2, new_y2;
    
    if (direction == 0) { // Left
        new_x1 = line->x1 - 1;
        new_y1 = line->y1;
        new_x2 = line->x2 - 1;
        new_y2 = line->y2;
    } else if (direction == 1) { // Up
        new_x1 = line->x1;
        new_y1 = line->y1 + 1;
        new_x2 = line->x2;
        new_y2 = line->y2 + 1;
    } else if (direction == 2) { // Right
        new_x1 = line->x1 + 1;
        new_y1 = line->y1;
        new_x2 = line->x2 + 1;
        new_y2 = line->y2;
    } else { // Down
        new_x1 = line->x1;
        new_y1 = line->y1 - 1;
        new_x2 = line->x2;
        new_y2 = line->y2 - 1;
    }
    
    for (int i = 0; i < n; i++) {
        if (i != idx && 
            (new_x1 >= lines[i].x1 && new_x1 <= lines[i].x2 && new_y1 >= lines[i].y1 && new_y1 <= lines[i].y2 ||
             new_x2 >= lines[i].x1 && new_x2 <= lines[i].x2 && new_y2 >= lines[i].y1 && new_y2 <= lines[i].y2)) {
            return 1;
        }
    }
    return 0;
}

void find_first_illegal_move() {
    for (int i = 0; i < n; i++) {
        if (check_collision(moves[i][0], moves[i][1])) {
            printf("%d\n", i + 1);
            return;
        }
    }
}

void print_valid_moves() {
    for (int i = 0; i < n; i++) {
        if (!check_collision(moves[i][0], moves[i][1])) {
            printf("%d %d %d %d\n", lines[moves[i][0]].x1, lines[moves[i][0]].y1, lines[moves[i][0]].x2, lines[moves[i][0]].y2);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &lines[i].x1, &lines[i].y1, &lines[i].x2, &lines[i].y2);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &moves[i][0], &moves[i][1]);
    }
    
    find_first_illegal_move();
    print_valid_moves();
    
    return 0;
}