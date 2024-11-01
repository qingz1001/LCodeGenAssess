#include <stdio.h>
#include <stdbool.h>

bool is_palindrome(int num) {
    int original_num = num;
    int reversed_num = 0;

    while (num > 0) {
        reversed_num = reversed_num * 10 + num % 10;
        num /= 10;
    }

    return original_num == reversed_num;
}

bool is_dual_palindrome(int num) {
    int count = 0;

    for (int base = 2; base <= 10; base++) {
        if (is_palindrome(num)) {
            count++;
        }
        num /= base;
    }

    return count >= 2;
}

int main() {
    int n, s;
    scanf("%d %d", &n, &s);

    int found = 0;
    for (int i = s + 1; found < n; i++) {
        if (is_dual_palindrome(i)) {
            printf("%d\n", i);
            found++;
        }
    }

    return 0;
}