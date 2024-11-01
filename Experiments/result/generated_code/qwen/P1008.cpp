#include <stdio.h>

int main() {
    int i, j, k;
    for (i = 1; i <= 9; i++) {
        for (j = 1; j <= 9; j++) {
            if (j == i) continue;
            for (k = 1; k <= 9; k++) {
                if (k == i || k == j) continue;
                int num1 = i * 100 + j * 10 + k;
                int num2 = 2 * num1;
                int num3 = 3 * num1;
                if (num2 / 100 == num3 / 100 && num2 % 100 == num3 % 100) {
                    printf("%d %d %d\n", num1, num2, num3);
                }
            }
        }
    }
    return 0;
}