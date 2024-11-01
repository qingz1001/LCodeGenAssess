#include <stdio.h>
#include <string.h>

#define MAX_N 250005

int n;
char s[MAX_N];
int x[MAX_N], y[MAX_N];
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
char dir[4] = {'N', 'E', 'S', 'W'};

struct Point {
    int x, y;
};

struct Line {
    int len;
    int start, end;
    char direction;
};

struct Line findShortestShortcut() {
    struct Line result = {MAX_N, 0, 0, 'N'};
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int ax = x[i], ay = y[i];
            int bx = x[j], by = y[j];
            if ((ax == bx && ay != by) || (ax != bx && ay == by)) {
                int min_x = (ax < bx) ? ax : bx;
                int max_x = (ax > bx) ? ax : bx;
                int min_y = (ay < by) ? ay : by;
                int max_y = (ay > by) ? ay : by;
                int shortcut_len = MAX_N;
                int shortcut_start = 0;
                int shortcut_end = 0;
                char shortcut_dir = 'N';
                for (int k = 0; k < 4; k++) {
                    int cx = min_x + dx[k];
                    int cy = min_y + dy[k];
                    if (cx >= 0 && cx <= max_x && cy >= 0 && cy <= max_y) {
                        int len = (cx - ax) * (cx - ax) + (cy - ay) * (cy - ay);
                        if (len < shortcut_len) {
                            shortcut_len = len;
                            shortcut_start = i;
                            shortcut_end = j;
                            shortcut_dir = dir[k];
                        } else if (len == shortcut_len) {
                            if (shortcut_start > i) {
                                shortcut_start = i;
                            } else if (shortcut_start == i && shortcut_end < j) {
                                shortcut_end = j;
                            }
                        }
                    }
                }
                if (shortcut_len < result.len) {
                    result.len = shortcut_len;
                    result.start = shortcut_start;
                    result.end = shortcut_end;
                    result.direction = shortcut_dir;
                } else if (shortcut_len == result.len) {
                    if (result.start > shortcut_start) {
                        result.start = shortcut_start;
                    } else if (result.start == shortcut_start && result.end < shortcut_end) {
                        result.end = shortcut_end;
                    }
                }
            }
        }
    }
    return result;
}

int main() {
    scanf("%d", &n);
    scanf("%s", s);
    x[0] = y[0] = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'N') {
            y[i + 1] = y[i] + 1;
            x[i + 1] = x[i];
        } else if (s[i] == 'S') {
            y[i + 1] = y[i] - 1;
            x[i + 1] = x[i];
        } else if (s[i] == 'E') {
            y[i + 1] = y[i];
            x[i + 1] = x[i] + 1;
        } else if (s[i] == 'W') {
            y[i + 1] = y[i];
            x[i + 1] = x[i] - 1;
        }
    }
    struct Line shortestShortcut = findShortestShortcut();
    printf("%d %d %d %c\n", shortestShortcut.len, shortestShortcut.start, shortestShortcut.end, shortestShortcut.direction);
    return 0;
}