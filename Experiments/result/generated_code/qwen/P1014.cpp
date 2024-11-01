#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);

    int sum = 0, row = 0, col = 0;

    while (sum < N) {
        row++;
        sum += row;
    }

    if ((row % 2) == 0) {
        col = sum - N + 1;
        printf("%d/%d\n", row - col, col);
    } else {
        col = N - (sum - row);
        printf("%d/%d\n", col, row - col);
    }

    return 0;
}