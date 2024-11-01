#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000
#define MAX_COORD 10000

int main() {
    int n;
    scanf("%d", &n);
    int rectangles[MAX_N][4];

    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &rectangles[i][0], &rectangles[i][1], &rectangles[i][2], &rectangles[i][3]);
    }

    int area = 0;

    for (int x = 0; x <= MAX_COORD; x++) {
        for (int y = 0; y <= MAX_COORD; y++) {
            int inside_count = 0;
            for (int i = 0; i < n; i++) {
                if (rectangles[i][0] <= x && x <= rectangles[i][2] && rectangles[i][1] <= y && y <= rectangles[i][3]) {
                    inside_count++;
                }
            }
            if (inside_count % 2 != 0) {
                area++;
            }
        }
    }

    printf("%d\n", area);

    return 0;
}