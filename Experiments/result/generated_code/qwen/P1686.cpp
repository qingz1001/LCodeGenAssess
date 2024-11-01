#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    char moves[n + 1];
    scanf("%s", moves);

    int x = 0, y = 0;
    for (int i = 0; i < n; i++) {
        if (moves[i] == 'N') y++;
        else if (moves[i] == 'S') y--;
        else if (moves[i] == 'E') x++;
        else if (moves[i] == 'W') x--;
    }

    int min_length = abs(x) + abs(y);
    int start_point = 0, end_point = n;
    char direction;

    if (x > 0) {
        direction = 'E';
        end_point = n - x;
    } else if (x < 0) {
        direction = 'W';
        start_point = -x;
    } else if (y > 0) {
        direction = 'N';
        end_point = n - y;
    } else if (y < 0) {
        direction = 'S';
        start_point = -y;
    }

    printf("%d %d %d %c\n", min_length, start_point, end_point, direction);

    return 0;
}