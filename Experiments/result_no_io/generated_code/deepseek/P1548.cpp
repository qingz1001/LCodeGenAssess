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

    // Calculate the number of rectangles
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            for (int k = i + 1; k <= N; k++) {
                for (int l = j + 1; l <= M; l++) {
                    rectangles++;
                }
            }
        }
    }

    // Subtract the number of squares from the total rectangles to get non-square rectangles
    rectangles -= squares;

    printf("%d %d\n", squares, rectangles);

    return 0;
}