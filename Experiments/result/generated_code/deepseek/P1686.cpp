#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x, y;
} Point;

int main() {
    int n;
    scanf("%d", &n);
    char *directions = (char *)malloc((n + 1) * sizeof(char));
    scanf("%s", directions);

    Point *points = (Point *)malloc((n + 1) * sizeof(Point));
    points[0].x = 0;
    points[0].y = 0;

    for (int i = 1; i <= n; i++) {
        points[i] = points[i - 1];
        switch (directions[i - 1]) {
            case 'N': points[i].y++; break;
            case 'S': points[i].y--; break;
            case 'E': points[i].x++; break;
            case 'W': points[i].x--; break;
        }
    }

    int min_length = n + 1;
    int start = 0, end = 0;
    char direction = ' ';

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (points[i].x == points[j].x) {
                int length = abs(points[i].y - points[j].y);
                if (length < min_length || (length == min_length && i < start) || (length == min_length && i == start && j > end)) {
                    min_length = length;
                    start = i;
                    end = j;
                    direction = (points[i].y < points[j].y) ? 'N' : 'S';
                }
            } else if (points[i].y == points[j].y) {
                int length = abs(points[i].x - points[j].x);
                if (length < min_length || (length == min_length && i < start) || (length == min_length && i == start && j > end)) {
                    min_length = length;
                    start = i;
                    end = j;
                    direction = (points[i].x < points[j].x) ? 'E' : 'W';
                }
            }
        }
    }

    printf("%d %d %d %c\n", min_length, start, end, direction);

    free(directions);
    free(points);
    return 0;
}