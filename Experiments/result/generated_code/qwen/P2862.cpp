#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500
#define MAX_XY 10000

int main() {
    int C, N;
    scanf("%d %d", &C, &N);

    int fields[MAX_N][2];
    for (int i = 0; i < N; ++i) {
        scanf("%d %d", &fields[i][0], &fields[i][1]);
    }

    // Find the minimum and maximum x and y coordinates
    int min_x = MAX_XY, max_x = 0, min_y = MAX_XY, max_y = 0;
    for (int i = 0; i < N; ++i) {
        if (fields[i][0] < min_x) min_x = fields[i][0];
        if (fields[i][0] > max_x) max_x = fields[i][0];
        if (fields[i][1] < min_y) min_y = fields[i][1];
        if (fields[i][1] > max_y) max_y = fields[i][1];
    }

    // Calculate the width and height of the bounding box
    int width = max_x - min_x + 1;
    int height = max_y - min_y + 1;

    // Iterate over possible side lengths starting from C
    for (int side = C; side <= width && side <= height; ++side) {
        int count = 0;
        for (int i = 0; i <= width - side; ++i) {
            for (int j = 0; j <= height - side; ++j) {
                int found = 0;
                for (int k = 0; k < N; ++k) {
                    if (fields[k][0] >= min_x + i && fields[k][0] < min_x + i + side &&
                        fields[k][1] >= min_y + j && fields[k][1] < min_y + j + side) {
                        found = 1;
                        break;
                    }
                }
                if (found) count++;
                if (count == C) {
                    printf("%d\n", side);
                    return 0;
                }
            }
        }
    }

    printf("No valid square found\n");
    return 0;
}