#include <stdio.h>

int is_valid(int num, int digits[], int n) {
    while (num > 0) {
        int digit = num % 10;
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (digits[i] == digit) {
                found = 1;
                break;
            }
        }
        if (!found) return 0;
        num /= 10;
    }
    return 1;
}

int main() {
    int n;
    scanf("%d", &n);
    int digits[9];
    for (int i = 0; i < n; i++) {
        scanf("%d", &digits[i]);
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                int num1 = digits[i] * 100 + digits[j] * 10 + digits[k];
                for (int l = 0; l < n; l++) {
                    for (int m = 0; m < n; m++) {
                        int num2 = digits[l] * 10 + digits[m];
                        int part1 = num1 * digits[m];
                        int part2 = num1 * digits[l];
                        int result = num1 * num2;
                        if (part1 >= 100 && part1 <= 999 && part2 >= 100 && part2 <= 999 && result >= 1000 && result <= 9999) {
                            if (is_valid(part1, digits, n) && is_valid(part2, digits, n) && is_valid(result, digits, n)) {
                                count++;
                            }
                        }
                    }
                }
            }
        }
    }

    printf("%d\n", count);
    return 0;
}