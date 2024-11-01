#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500
#define MAX_C 500
#define MAX_XY 10000

int main() {
    int C, N;
    scanf("%d %d", &C, &N);

    int fields[MAX_XY + 1][MAX_XY + 1] = {0};
    int x, y;

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &x, &y);
        fields[x][y]++;
    }

    int min_side_length = MAX_XY - 1;

    for (int i = 1; i <= MAX_XY && min_side_length > 0; i++) {
        for (int j = 1; j <= MAX_XY && min_side_length > 0; j++) {
            int count = 0;
            for (int k = i; k <= i + min_side_length && count < C; k++) {
                for (int l = j; l <= j + min_side_length && count < C; l++) {
                    if (fields[k][l] > 0) {
                        count++;
                    }
                }
            }
            if (count >= C) {
                min_side_length = i;
            }
        }
    }

    printf("%d\n", min_side_length);

    return 0;
}