#include <stdio.h>

// 计算magic函数
int magic(int n) {
    int prev_digit = n % 10;
    n /= 10;
    int new_number = 0;
    while (n > 0) {
        int current_digit = n % 10;
        new_number = new_number * 10 + abs(current_digit - prev_digit);
        prev_digit = current_digit;
        n /= 10;
    }
    return new_number;
}

// 判断是否是幸运数
int is_lucky(int n) {
    while (n >= 10) {
        n = magic(n);
    }
    return n == 7;
}

int main() {
    int A, B;
    scanf("%d %d", &A, &B);
    int count = 0;
    for (int i = A; i <= B; ++i) {
        if (is_lucky(i)) {
            count++;
        }
    }
    printf("%d\n", count);
    return 0;
}