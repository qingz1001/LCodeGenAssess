#include <stdio.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    long long squares = 0;
    long long rectangles = 0;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            squares += (N - i + 1) * (M - j + 1);
            if (i != j) {
                rectangles += (N - i + 1) * (M - j + 1) * 2;
            }
        }
    }

    printf("%lld %lld\n", squares, rectangles);

    return 0;
}