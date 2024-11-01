#include <stdio.h>
#include <stdlib.h>

#define MAXN 200
#define MAXM 200
#define MAX_DIFF 16315

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int a[MAXN][MAXM];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    int max_area = 0;
    for (int height = -MAX_DIFF; height <= MAX_DIFF; height++) {
        int left[MAXM], right[MAXM], up[MAXM], down[MAXM];
        for (int j = 0; j < M; j++) {
            left[j] = right[j] = j;
            up[j] = down[j] = 0;
        }
        for (int i = 0; i < N; i++) {
            int min_left = 0, max_right = M - 1;
            for (int j = 0; j < M; j++) {
                if (a[i][j] < height) {
                    left[j] = j + 1;
                    min_left = j + 1;
                }
                if (a[i][j] > height) {
                    right[j] = j - 1;
                    max_right = j - 1;
                }
            }
            for (int j = 0; j < M; j++) {
                left[j] = (left[j] > min_left) ? min_left : left[j];
                right[j] = (right[j] < max_right) ? max_right : right[j];
                up[j] = i + 1;
            }
            for (int j = 0; j < M; j++) {
                if (left[j] <= right[j]) {
                    int area = (right[j] - left[j] + 1) * (i + 1);
                    if (area > max_area) {
                        max_area = area;
                    }
                }
            }
        }
    }

    printf("%d\n", max_area);
    return 0;
}