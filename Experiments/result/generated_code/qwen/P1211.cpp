#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 10

int is_prime(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int count_cryptarithms(int digits[], int n) {
    int count = 0;
    for (int a = 0; a < n; a++) {
        for (int b = 0; b < n; b++) {
            if (b == a) continue;
            for (int c = 0; c < n; c++) {
                if (c == a || c == b) continue;
                for (int d = 0; d < n; d++) {
                    if (d == a || d == b || d == c) continue;
                    for (int e = 0; e < n; e++) {
                        if (e == a || e == b || e == c || e == d) continue;
                        int first = digits[a] * 100 + digits[b] * 10 + digits[c];
                        int second = digits[d] * 10 + digits[e];
                        int product = first * second;
                        int part1 = digits[a] * 10 + digits[b];
                        int part2 = digits[c] * 10 + digits[d];
                        int result = part1 * 100 + part2 * 10 + product;
                        if (product == digits[e] && result == product * 10) {
                            count++;
                        }
                    }
                }
            }
        }
    }
    return count;
}

int main() {
    int n;
    scanf("%d", &n);
    int digits[MAX_NUM];
    for (int i = 0; i < n; i++) {
        scanf("%d", &digits[i]);
    }
    printf("%d\n", count_cryptarithms(digits, n));
    return 0;
}