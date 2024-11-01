#include <stdio.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int quotient = N / M;
    int remainder = N % M;

    for (int i = 0; i < M; i++) {
        if (remainder > 0) {
            printf("%d ", quotient + 1);
            remainder--;
        } else {
            printf("%d ", quotient);
        }
    }

    return 0;
}