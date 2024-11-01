#include <stdio.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int squares = 0;
    int rectangles = 0;

    // Calculate the number of squares
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            squares += (N - i + 1) * (M - j + 1);
        }
    }

    // Calculate the number of rectangles (excluding squares)
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            for (int k = i + 1; k <= N; k++) {
                for (int l = j + 1; l <= M; l++) {
                    rectangles += (N - k + 1) * (M - l + 1);
                }
            }
        }
    }

    printf("%d %d\n", squares, rectangles);

    return 0;
}