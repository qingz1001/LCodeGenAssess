#include <stdio.h>

int is_valid(int num) {
    int digits[10] = {0};
    while (num > 0) {
        int digit = num % 10;
        if (digit == 0 || digits[digit] == 1) return 0;
        digits[digit] = 1;
        num /= 10;
    }
    return 1;
}

int main() {
    int A, B, C;
    scanf("%d %d %d", &A, &B, &C);

    int found = 0;
    for (int i = 123; i <= 987; i++) {
        int j = i * B / A;
        int k = i * C / A;
        if (j > 987 || k > 987) continue;
        if (is_valid(i * 1000000 + j * 1000 + k)) {
            printf("%d %d %d\n", i, j, k);
            found = 1;
        }
    }

    if (!found) {
        printf("No!!!\n");
    }

    return 0;
}