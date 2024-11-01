#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);

    int row = 1, col = 1;
    int sum = 1;

    while (sum < N) {
        if (row == 1) {
            col++;
            sum++;
            if (sum == N) break;

            while (col > 1) {
                row++;
                col--;
                sum++;
                if (sum == N) break;
            }
        } else {
            row++;
            sum++;
            if (sum == N) break;

            while (row > 1) {
                row--;
                col++;
                sum++;
                if (sum == N) break;
            }
        }
    }

    printf("%d/%d\n", row, col);

    return 0;
}