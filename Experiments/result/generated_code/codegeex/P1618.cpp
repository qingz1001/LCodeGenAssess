#include <stdio.h>

int main() {
    int A, B, C;
    scanf("%d%d%d", &A, &B, &C);

    int digits[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (int i = 0; i < 8; i++) {
        for (int j = i + 1; j < 9; j++) {
            for (int k = j + 1; k < 9; k++) {
                int num1 = digits[i] * 100 + digits[j] * 10 + digits[k];
                int num2 = num1 * B / A;
                int num3 = num1 * C / A;

                if (num2 < 100 || num2 > 999 || num3 < 100 || num3 > 999) continue;

                int check[10] = {0};
                check[digits[i]]++;
                check[digits[j]]++;
                check[digits[k]]++;
                check[num1 / 100]++;
                check[num1 % 100 / 10]++;
                check[num1 % 10]++;
                check[num2 / 100]++;
                check[num2 % 100 / 10]++;
                check[num2 % 10]++;
                check[num3 / 100]++;
                check[num3 % 100 / 10]++;
                check[num3 % 10]++;

                int valid = 1;
                for (int l = 1; l <= 9; l++) {
                    if (check[l] != 1) {
                        valid = 0;
                        break;
                    }
                }

                if (valid) {
                    printf("%d %d %d\n", num1, num2, num3);
                }
            }
        }
    }

    return 0;
}