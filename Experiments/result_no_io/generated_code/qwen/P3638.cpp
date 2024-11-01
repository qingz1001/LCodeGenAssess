#include <stdio.h>
#include <stdlib.h>

#define MAX_N 9
#define MAX_W 500
#define MAX_H 500

typedef struct {
    int x, y;
    char dir; // 'L' for left, 'R' for right, 'U' for up, 'D' for down
} Robot;

int n, w, h;
char grid[MAX_H][MAX_W];
Robot robots[MAX_N];

void push_robot(int idx) {
    int x = robots[idx].x, y = robots[idx].y;
    while (1) {
        switch (robots[idx].dir) {
            case 'L':
                if (y > 0 && grid[x][y - 1] != 'x') {
                    y--;
                } else {
                    break;
                }
                break;
            case 'R':
                if (y < w - 1 && grid[x][y + 1] != 'x') {
                    y++;
                } else {
                    break;
                }
                break;
            case 'U':
                if (x > 0 && grid[x - 1][y] != 'x') {
                    x--;
                } else {
                    break;
                }
                break;
            case 'D':
                if (x < h - 1 && grid[x + 1][y] != 'x') {
                    x++;
                } else {
                    break;
                }
                break;
        }
        if (grid[x][y] == 'A') {
            robots[idx].dir = (robots[idx].dir == 'L') ? 'D' : 
                             (robots[idx].dir == 'R') ? 'U' : 
                             (robots[idx].dir == 'U') ? 'R' : 'L';
        } else if (grid[x][y] == 'C') {
            robots[idx].dir = (robots[idx].dir == 'L') ? 'U' : 
                             (robots[idx].dir == 'R') ? 'D' : 
                             (robots[idx].dir == 'U') ? 'L' : 'R';
        } else {
            break;
        }
    }
    robots[idx].x = x;
    robots[idx].y = y;
}

int can_merge(Robot a, Robot b) {
    return abs(a.x - b.x) + abs(a.y - b.y) == 1;
}

void merge_robots(int idx1, int idx2) {
    int min_idx = (a.idx < b.idx) ? a.idx : b.idx;
    int max_idx = (a.idx < b.idx) ? b.idx : a.idx;
    robots[min_idx].x = robots[max_idx].x;
    robots[min_idx].y = robots[max_idx].y;
    robots[min_idx].dir = 'U'; // Assuming vertical merge for simplicity
    robots[max_idx].x = -1; // Mark as merged
    robots[max_idx].y = -1;
}

int main() {
    scanf("%d %d %d", &n, &w, &h);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            scanf(" %c", &grid[i][j]);
            if ('1' <= grid[i][j] && grid[i][j] <= '9') {
                robots[grid[i][j] - '1'] = (Robot){i, j, 'R'};
            }
        }
    }

    int moves = 0;
    int merged = 0;
    while (merged < n - 1) {
        for (int i = 0; i < n; i++) {
            if (robots[i].x == -1) continue;
            push_robot(i);
            for (int j = i + 1; j < n; j++) {
                if (can_merge(robots[i], robots[j])) {
                    merge_robots(i, j);
                    merged++;
                    moves++;
                    break;
                }
            }
        }
    }

    if (merged == n - 1) {
        printf("%d\n", moves);
    } else {
        printf("-1\n");
    }

    return 0;
}