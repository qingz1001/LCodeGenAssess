#include <stdio.h>

int count_digit_2(int num) {
    int count = 0;
    while (num > 0) {
        if (num % 10 == 2) {
            count++;
        }
        num /= 10;
    }
    return count;
}

int main() {
    int L, R;
    scanf("%d %d", &L, &R);
    int total_count = 0;
    for (int i = L; i <= R; i++) {
        total_count += count_digit_2(i);
    }
    printf("%d\n", total_count);
    return 0;
}