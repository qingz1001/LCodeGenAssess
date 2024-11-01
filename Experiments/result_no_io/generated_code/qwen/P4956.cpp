#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);

    int max_X = 0, min_K = 100;

    for (int X = 1; X <= 100; X++) {
        for (int K = 1; K < 100; K++) {
            int total = 0;
            for (int i = 0; i < 52; i++) {
                total += X + i * K;
            }
            if (total == N) {
                if (X > max_X || (X == max_X && K < min_K)) {
                    max_X = X;
                    min_K = K;
                }
            }
        }
    }

    printf("%d\n%d\n", max_X, min_K);

    return 0;
}