#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    char s[250005];
    scanf("%s", s);

    int x = 0, y = 0;
    int points[250005][2];
    points[0][0] = 0;
    points[0][1] = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] == 'N') y++;
        else if (s[i] == 'S') y--;
        else if (s[i] == 'E') x++;
        else if (s[i] == 'W') x--;
        points[i + 1][0] = x;
        points[i + 1][1] = y;
    }

    int min_length = 0x7fffffff;
    int start_point = 0, end_point = 0, direction = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int dx = points[i][0] - points[j][0];
            int dy = points[i][1] - points[j][1];
            int length = dx * dx + dy * dy;
            if (length < min_length) {
                min_length = length;
                start_point = i;
                end_point = j;
                if (dx == 0) {
                    direction = (dy > 0) ? 'N' : 'S';
                } else {
                    direction = (dx > 0) ? 'E' : 'W';
                }
            } else if (length == min_length) {
                if (start_point > i || (start_point == i && end_point < j)) {
                    start_point = i;
                    end_point = j;
                    if (dx == 0) {
                        direction = (dy > 0) ? 'N' : 'S';
                    } else {
                        direction = (dx > 0) ? 'E' : 'W';
                    }
                }
            }
        }
    }

    printf("%d %d %d %c\n", min_length, start_point, end_point, direction);
    return 0;
}