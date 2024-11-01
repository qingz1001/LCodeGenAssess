#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);

    int row = 1;
    while (N > row) {
        N -= row;
        row++;
    }

    if (row % 2 == 1) {
        printf("%d/%d\n", row - N + 1, N);
    } else {
        printf("%d/%d\n", N, row - N + 1);
    }

    return 0;
}