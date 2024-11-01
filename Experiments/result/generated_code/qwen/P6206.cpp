#include <stdio.h>

int main() {
    int N, score = 0;
    scanf("%d", &N);
    while (N != 1) {
        if (N % 2 == 0) {
            N /= 2;
        } else {
            N = 3 * N + 1;
        }
        score++;
    }
    printf("%d\n", score);
    return 0;
}