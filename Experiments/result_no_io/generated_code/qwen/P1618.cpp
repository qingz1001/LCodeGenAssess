#include <stdio.h>
#include <stdlib.h>

int main() {
    int A, B, C;
    scanf("%d %d %d", &A, &B, &C);

    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            if (j == i) continue;
            for (int k = 1; k <= 9; k++) {
                if (k == i || k == j) continue;

                int num1 = i * 100 + j * 10 + k;
                int num2 = k * 100 + i * 10 + j;
                int num3 = j * 100 + k * 10 + i;

                if ((num1 * B * C == num2 * A * C) && (num1 * B * C == num3 * A * B)) {
                    printf("%d %d %d\n", num1, num2, num3);
                }
            }
        }
    }

    return 0;
}