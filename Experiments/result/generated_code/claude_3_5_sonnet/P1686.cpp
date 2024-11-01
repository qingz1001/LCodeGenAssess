#include <stdio.h>
#include <string.h>

#define MAX_N 250001

int x[MAX_N], y[MAX_N];
char dir[MAX_N];

int main() {
    int n;
    scanf("%d", &n);
    scanf("%s", dir);

    int cx = 0, cy = 0;
    x[0] = y[0] = 0;
    
    for (int i = 0; i < n; i++) {
        switch(dir[i]) {
            case 'N': cy++; break;
            case 'S': cy--; break;
            case 'E': cx++; break;
            case 'W': cx--; break;
        }
        x[i+1] = cx;
        y[i+1] = cy;
    }

    int best_len = n, best_start = 0, best_end = n;
    char best_dir = 'N';

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int dx = x[j] - x[i];
            int dy = y[j] - y[i];
            int len = (dx != 0) ? dx : dy;
            if (len < 0) len = -len;

            if ((dx == 0 || dy == 0) && len < j - i && len < best_len) {
                best_len = len;
                best_start = i;
                best_end = j;
                if (dx > 0) best_dir = 'E';
                else if (dx < 0) best_dir = 'W';
                else if (dy > 0) best_dir = 'N';
                else best_dir = 'S';
            }
        }
    }

    printf("%d %d %d %c\n", best_len, best_start, best_end, best_dir);

    return 0;
}