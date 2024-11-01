#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 5000
#define MAX_COORD 20001
#define OFFSET 10000

typedef struct {
    int x1, y1, x2, y2;
} Rectangle;

Rectangle rects[MAX_N];
int N;
int horizontal[MAX_COORD][2], vertical[MAX_COORD][2];

void addLine(int a, int b, int c, int isHorizontal) {
    int *line = isHorizontal ? horizontal[c + OFFSET] : vertical[c + OFFSET];
    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }
    if (line[0] == 0 || a < line[0]) line[0] = a;
    if (line[1] == 0 || b > line[1]) line[1] = b;
}

int calculatePerimeter() {
    int perimeter = 0;
    for (int i = 0; i < MAX_COORD; i++) {
        if (horizontal[i][0] != horizontal[i][1]) {
            perimeter += horizontal[i][1] - horizontal[i][0];
        }
        if (vertical[i][0] != vertical[i][1]) {
            perimeter += vertical[i][1] - vertical[i][0];
        }
    }
    return perimeter;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d %d", &rects[i].x1, &rects[i].y1, &rects[i].x2, &rects[i].y2);
        addLine(rects[i].x1, rects[i].x2, rects[i].y1, 1);
        addLine(rects[i].x1, rects[i].x2, rects[i].y2, 1);
        addLine(rects[i].y1, rects[i].y2, rects[i].x1, 0);
        addLine(rects[i].y1, rects[i].y2, rects[i].x2, 0);
    }

    int result = calculatePerimeter();
    printf("%d\n", result);

    return 0;
}