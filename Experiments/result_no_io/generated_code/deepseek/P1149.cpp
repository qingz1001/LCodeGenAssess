#include <stdio.h>

int matchsticks[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6}; // 数字0-9所需的火柴棒数量

int countMatches(int num) {
    if (num == 0) return matchsticks[0];
    int count = 0;
    while (num > 0) {
        count += matchsticks[num % 10];
        num /= 10;
    }
    return count;
}

int main() {
    int n;
    scanf("%d", &n);

    int totalMatches = n - 4; // 减去加号和等号的4根火柴
    int count = 0;

    for (int A = 0; A <= 1000; A++) {
        for (int B = 0; B <= 1000; B++) {
            int C = A + B;
            if (countMatches(A) + countMatches(B) + countMatches(C) == totalMatches) {
                count++;
            }
        }
    }

    printf("%d\n", count);
    return 0;
}